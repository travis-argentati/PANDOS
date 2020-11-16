#include "../h/const.h"
#include "../h/types.h"

/*#include "p2test.c"*/
#include "/usr/local/include/umps3/umps/libumps.h"

#include "../h/initial.h"
#include "../h/scheduler.h"
#include "../h/exceptions.h"
#include "../h/interrupts.h"
#include "../h/asl.h"
#include "../h/pcb.h"


cpu_t stopTOD;


void interruptHandler(){

  /*
  Who interrupted me?
  What line number? It will be in the cause Register
  Which device?
=======
 /* who interrupted?
 handle one interrupt at a time (highest priority)
    for this we need:
        line number (in cause register)
        which device it was (look at interrupting device's bit map) */
  STCK(stopTOD);
  int timeLeft = getTIMER();
  unsigned int intCause = ((state_t*) BIOSDATAPAGE) -> s_cause;
  // unsigned int intStatus= ((state_t*) BIOSDATAPAGE) -> s_status;

/*
-local Timer
-interval Timer
- dlashes, disks, terminals, printers

disksCode & intCause !=0
*/
  if((intCause & 0x00000200) != 0){
    pltInterrupts(stopTOD);
  } if((intCause & 0x0000400) != 0){
    intervaltimerInterrupts();
  } if((intCause & 0x0000800) != 0) {
    deviceInterrupts(DISKINT);
  } if((intCause & 0x0001000) != 0){
    deviceInterrupts(3);
    flashInterrupts(FLASHINT);
  } if((intCause & 0x0002000) != 0){
    deviceInterrupts(NETWINT);
    networkInterrupts(NETWINT);
  } if((intCause & 0x0004000) != 0) {
    deviceInterrupts(3);
    printerInterrupts(PRNTINT);
  } if((intCause & 0x0008000) != 0){
    deviceInterrupts(TERMINT);
    // terminalInterrupts(TERMINT);
  }

  if(currentProcess != NULL){
    PANIC();
    currentProcess -> p_time = currentProcess -> p_time + (stopTOD - startTOD);

    // transferState(intStatus/*((state_t*) BIOSDATAPAGE) -> s_status*/, &(currentProcess -> p_s));
    transferState(((state_t*) BIOSDATAPAGE), &(currentProcess -> p_s));

    prepareSwitch(currentProcess, timeLeft);
  }


}

void pltInterrupts(int stopTOD){
  if(currentProcess != NULL){
    // terminalInterrupts(TERMINT);
    currentProcess -> p_time = currentProcess -> p_time + (stopTOD - startTOD);
    // printerInterrupts(PRNTINT);
    transferState(((state_t*)BIOSDATAPAGE)/* -> s_status */, &(currentProcess -> p_s));
    // printerInterrupts(PRNTINT);
    insertProcQ(&readyQueue, currentProcess);
    // printerInterrupts(PRNTINT);
    scheduler();
  } else {
    PANIC();
  }

}

void intervaltimerInterrupts(){
  LDIT(100000);
  pcb_t *temp = removeBlocked(&clockSem);
  while(temp != NULL){
    insertProcQ(&readyQueue, temp);
    softBlockedCount++;
    temp = removeBlocked(&clockSem);
  }

  clockSem = 0;

  if(currentProcess == NULL){
    scheduler();
  }

}

void deviceInterrupts(int lineNum){

  unsigned int deviceNum = 0;
  int deviceDetermined = FALSE;
  unsigned int deviceTransmStatus;

  volatile devregarea_t *temp = (devregarea_t *) RAMBASEADDR;
  unsigned int interruptBitMap = temp -> interrupt_dev[lineNum - DISKINT];

  /* Check to see if the interruptBitMap has anything it in, if not something went wrong */
  if(&(interruptBitMap) == NULL){
    PANIC();
  }

  if((interruptBitMap & 0x00000001) != 0){
    deviceNum = 0;
    deviceDetermined = TRUE;
  }
  if(((interruptBitMap & 0x00000002) && deviceDetermined) != 0){
    deviceNum = 1;
    deviceDetermined = TRUE;
    PANIC();
  }
  if(((interruptBitMap & 0x00000004) && deviceDetermined) != 0){
    deviceNum = 2;
    deviceDetermined = TRUE;
    PANIC();
  }
  if(((interruptBitMap & 0x00000008) && deviceDetermined) != 0){
    deviceNum = 3;
    deviceDetermined = TRUE;
    PANIC();
  }
  if(((interruptBitMap & 0x00000010) && deviceDetermined) != 0){
    deviceNum = 4;
    deviceDetermined = TRUE;
    PANIC();
  }
  if(((interruptBitMap & 0x00000020) && deviceDetermined) != 0){
    deviceNum = 5;
    deviceDetermined = TRUE;
    PANIC();
  }
  if(((interruptBitMap & 0x00000040) && deviceDetermined) != 0){
    deviceNum = 6;
    deviceDetermined = TRUE;
    PANIC();
  }
  if(((interruptBitMap & 0x00000080) && deviceDetermined) != 0){
    deviceNum = 7;
    deviceDetermined = TRUE;
    PANIC();
  }
  deviceNum = (((lineNum - DISKINT) * DEVPERINT) + deviceNum);
  if(lineNum != 7){
    PANIC();
  } else {
    deviceTransmStatus = temp -> devreg[deviceNum].term.transm_status;
    //  Check if terminal Interrupt status is transmit
    // If not then terminal Interrupt status is receive
    if((deviceTransmStatus & 0x0F) != 1){
      temp -> devreg[deviceNum].term.transm_command = ACK;
    } else {
      temp -> devreg[deviceNum].term.recv_command = ACK;
    }
  }

  softBlockedCount--;
  // deviceSema4[deviceNum] = (int *) currentProcess -> p_s.s_a1;

  // deviceSema4[deviceNum]++;
  if(deviceSema4[deviceNum] <= 0){
    pcb_t *pseudoSys4 = removeBlocked(&deviceSema4[deviceNum]);
    pseudoSys4 -> p_s.s_v0 = deviceTransmStatus;
    if(pseudoSys4 != NULL){
      insertProcQ(&readyQueue, pseudoSys4);
    }
  }

  startTOD = getTIMER();
  if(currentProcess == NULL){
    scheduler();
  } else {
    contextSwitch(currentProcess);
  }



}

void flashInterrupts(int lineNum){

}

void networkInterrupts(int lineNum){

}

void printerInterrupts(int lineNum){

}

void terminalInterrupts(int lineNum){

}
