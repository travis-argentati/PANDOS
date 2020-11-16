#include "../h/const.h"
#include "../h/types.h"

/*#include "p2test.c"*/


#include "../h/initial.h"
#include "../h/scheduler.h"
#include "../h/exceptions.h"
#include "../h/interrupts.h"
#include "../h/asl.h"
#include "../h/pcb.h"

#include "/usr/local/include/umps3/umps/libumps.h"

extern void test();
extern void uTLB_RefillHandler();

/*HIDDEN void generalExceptionHandler();*/

/* Global variables */
int processCount;
int softBlockedCount;
pcb_t *currentProcess;
pcb_t *readyQueue;
cpu_t startTOD;
unsigned int deviceStat[DEVCOUNT+DEVPERINT];
int deviceSema4 [DEVCOUNT+DEVPERINT+1];
#define clockSem deviceSema4 [DEVCOUNT+DEVPERINT]

void main(){

  /* Initialize pass up vector */
  passupvector_t *passUpVector = (passupvector_t *) PASSUPVECTOR;
  passUpVector -> tlb_refll_handler = (memaddr) uTLB_RefillHandler;
  passUpVector -> tlb_refll_stackPtr = 0x20001000;
  passUpVector -> exception_handler = (memaddr) generalExpectionHandler;
  passUpVector -> exception_stackPtr = 0x20001000;

  /* Initialize process queue and semaphore queue */
  initPcbs();
  initASL();


  /* Set up empty ready queue and empty current process */
  currentProcess = NULL;
  readyQueue = mkEmptyProcQ();
  clockSem = 0;

  for (int i = 0; i < (DEVCOUNT+DEVPERINT); i++){
    deviceSema4[i] = 0;
  }

  LDIT(100000);

  memaddr ramTop;
  RAMTOP(ramTop);

  pcb_t *temp = allocPcb();
  if (temp != NULL) {
    temp -> p_s.s_pc = temp -> p_s.s_t9 = (memaddr)test;
    temp -> p_s.s_status = ALLOFF | INTERRUPTENABLED_P | IMON | TEON;
    temp -> p_s.s_sp = ramTop;
    processCount++;
    insertProcQ(&readyQueue, temp);

    /* call scheduler */
    scheduler();
  } else {
    PANIC();
  }
  return (0);
}


void generalExpectionHandler(){

  state_t *prevState = (state_t *) BIOSDATAPAGE;

  int exceptionType = (prevState -> s_cause &0x0000007C ) >> CAUSESHIFT;


  if(exceptionType == IOINTERRUPTS){
    interruptHandler();
  } if (exceptionType <= TLBINVLDS){
    uTLB_RefillHandler();
  } if (exceptionType == SYSEXCEPT){
    syscallHandler();
  }

  programTrapHandler();


}
