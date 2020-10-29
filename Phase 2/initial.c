#include "../h/const.h"
#include "../h/types.h"
#include "../h/initial.h"
#include "../h/asl.h"
#include "../h/pcb.h"

extern void test();
extern void uTLB_RefillHandler();

HIDDEN void generalExceptionHandler();

/* Global variables */
unsigned int devStat [DEVICECNT+DEVPERINT];
static int processCount;
static int softBlockedCount;
static pcb_t *currentProcess;
static pcb_t *readyQueue;
cpu_t startTOD;
cpu_t sliceCnt;
char msgbuf [50];
static int deviceSema4 [DEVICECNT+DEVPERINT+1];
#define clock deviceSema4 [DEVICECNT+DEVPERINT]

void main(){

  /* Local variables */
  int i;
  pcb_t *temp;
  memaddr ramTop;
  passupvector_t *passUpVector;

  /* Initialize pass up vector */
  passUpVector = (passupvector_t *) PASSUPVECTOR;
  passUpVector->tlb_refll_handler = (memaddr) uTLB_RefillHandler;
  passUpVector->tlb_refll_stackPtr = KERNELSTACK;
  passUpVector->execption_handler = (memaddr) generalExpectionHandler;
  passUpVector->exception_stackPtr = KERNELSTACK;

  /* Initialize process queue and semaphore queue */
  initPcbs();
  initASL();
  processCount = 0;
  softBlockedCount = 0;
  
  /* Set up empty ready queue and empty current process */
  currentProcess = NULL;
  readyQueue = mkEmptyProcQ();
  
  /*  */
  clock = 0;
  for (i = 0; i < (DEVICECNT+DEVPERINT); i++)
  deviceSema4[i] = 0;

  /*  */
  LDIT(PSECOND);

  /*  */
  RAMTOP(ramTop);
  
  temp = allocPcb();
  if (temp != NULL) {
    /*  */
    temp->p_s.s_pc = temp->p_s.s_t9 = (memaddr)test;
    temp->p_s.s_status = ALLOFF | IEPON | IMON | TEBITON;
    temp->p_s.s_sp = ramTop;
    processCount += 1;
    insertProcQ(&readyQueue, temp);

    /* call scheduler */
    switchProcess();
  }
  else {
    PANIC();
  }
  return (0);
} /* end of main */


void generalExpectionHandler(){

  /*
  Function: generalExceptionHandler
  Purpose: 
  Parameters: None  
  */

  /*  */
  state_PTR oldState;
  int exceptionCause;

  /*  */
  oldState = (state_PTR) BIOSDATAPAGE;
  exceptionCause = (oldState->s_cause & GETEXECCODE) >> CAUSESHIFT;
  if (exceptionCause == IOINTERRUPTS) intTrapHandler();
  if (exceptionCause <= TLBINVLDS) tlbTrapHandler();
  if (exceptionCause == SYSEXCEPTION) sysTrapHandler();

  /* everything else is a program trap and is handled be program trap handler */
  pgmTrapHandler();
}
