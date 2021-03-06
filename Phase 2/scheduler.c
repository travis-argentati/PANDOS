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


void scheduler(){

  terminalInterrupts(TERMINT);

  pcb_t *p = removeProcQ(&readyQueue);
  // p = removeProcQ(&readyQueue);
  /*
  if(&(p -> p_s) == ((state_t *)0x20007dd4)){
    p = removeProcQ(&readyQueue);
  }*//*
  if(&(p -> p_s) == ((state_t *)0x20006dd4)){
    p = removeProcQ(&readyQueue);
  }
  */


  if(p != NULL){
    prepareSwitch(p, 5000);
    // prepareSwitch(p, 9999999999999);
  }

  // if no more processes
  if(processCount == 0){
    // We are done with processes
    HALT();
  } else {
    if(softBlockedCount > 0){
      currentProcess = NULL;
      // setTIMER(9999999999999);
      setTIMER((unsigned int) 0xFFFFFFFF);
      unsigned int status = ALLOFF | IMON | INTERRUPTENABLED_C | TEON;
      setSTATUS(status);
      WAIT();
    } else {
      // We've reached deadlock and we must panic!
      PANIC();
    }
  }

}



void contextSwitch(pcb_t *currentProc){
  currentProcess = currentProc;
  // printerInterrupts(PRNTINT);
  LDST(&(currentProcess -> p_s));
}

void transferState(state_t *source, state_t *destination){

  for (int i = 0; i < STATEREGNUM; i++) {
    destination -> s_reg[i] = source -> s_reg[i];
  }

  destination -> s_pc = source -> s_pc;
  destination -> s_cause = source -> s_cause;
  destination -> s_status = source -> s_status;
  destination -> s_entryHI = source -> s_entryHI;
}

void prepareSwitch(pcb_t *currentProc, int timeSlice){
  STCK(startTOD);
  setTIMER(timeSlice);
  contextSwitch(currentProc);
}
