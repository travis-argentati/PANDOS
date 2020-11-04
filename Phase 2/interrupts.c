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


int stopTOD;

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
  unsigned int intStatus= ((state_t*) BIOSDATAPAGE) -> s_status;

/*
-local Timer
-interval Timer
- dlashes, disks, terminals, printers

disksCode & intCause !=0
*/
  if((intCause & PROCESSORLOCALTIMER) != 0){
    pltInterrupts(1);
  } if((intCause & INTERVALTIMER) != 0){
    intervaltimerInterrupts(2);
  } if((intCause & DISKINT) != 0) {
    deviceInterrupts(3);
  } if((intCause & FLASHINT) != 0){
    deviceInterrupts(3);
    flashInterrupts(FLASHINT);
  } if((intCause & NETWINT) != 0){
    deviceInterrupts(3);
    networkInterrupts(NETWINT);
  } if((intCause & PRNTINT) != 0) {
    deviceInterrupts(3);
    printerInterrupts(PRNTINT);
  } if((intCause & 0x0008000) != 0){
    deviceInterrupts(TERMINT);
    // terminalInterrupts(TERMINT);
  }

  if(currentProcess != NULL){
    currentProcess -> p_time = currentProcess -> p_time + (stopTOD - startTOD);

    transferState((state_t*) BIOSDATAPAGE, &(currentProcess -> p_s));
    prepareToSwitch(currentProcess, timeLeft);
  }

}

void pltInterrupts(int lineNum){

}

void intervaltimerInterrupts(int lineNum){

}

void deviceInterrupts(int lineNum){


  // if(lineNum = 7){
  // int devNum = ((state_t*)BUSREG).s_reg[];



  int deviceNum = currentProcess -> p_s.s_a2;
  unsigned int devBaseAddress = 10000054 + ((lineNum - 3) *0x80) + ((deviceNum) * 0x10);

  unsigned int statusCode = ((state_t*)devBaseAddress) -> s_status;

  verhogen();
  wait_For_IO_Devices();

  insertBlocked(lineNum, &readyQueue);
  contextSwitch(currentProcess);

  devregarea_t devTermArea;
  devreg_t devTerm;
  devTerm.term.transm_status = ACK;
  devTermArea.devreg[lineNum][deviceNum];

  // devregarea_t termBase = ((;

  // int termDev =
  // devreg_t termDev =

  // unsigned int dev = ((state_t*)BIOSDATAPAGE) -> s_status;


  // devreg_t termDev = ((devregarea_t) 0x10000054).devreg[((lineNum - 2) * 8) - 8];

   // devBaseAddress = 0x10000054 + ((lineNum - 3) *0x80) + ((devNum) * 0x10);
  // devregarea_t devBaseAddress = 0x10000054 + ((lineNum - 3) *0x80) + ((DEVPERINT) * 0x10);
  // devregarea_t devBaseAddress.devreg[9] = (unsigned int)((0x10000054) + ((lineNum - 3) *0x80) + ((1) * 0x10));


  // termreg_t termInt = (unsigned int)((0x10000054) + ((lineNum - 3) *0x80) + ((1) * 0x10));
  // termInt.transm_status = ACK;
  // devBaseAddress.devreg[((lineNum - 2) * 8) - 8].term.transm_status = ACK;

  // device_t interruptingDev = ((state_t*) devBaseAddress);

  // interruptingDev.s_reg[1].d_data0 = ACK;



  // ((state_t*) BIOSDATAPAGE) -> s_reg[];

}

void flashInterrupts(int lineNum){

}

void networkInterrupts(int lineNum){

}

void printerInterrupts(int lineNum){

}

void terminalInterrupts(int lineNum){

}
