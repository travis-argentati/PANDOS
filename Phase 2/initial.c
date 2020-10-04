#include "../h/const.h"
#include "../h/types.h"
#include "../h/initial.h"
#include "../h/asl.h"
#include "../h/pcb.h"


static int processCount;
static int softBlockedCount;
static pcb_t *readyQueue;
static pcb_t *currentProcess;
static int deviceSema4;

void main(){

  processCount = 0;
  softBlockedCount = 0;
  readyQueue = mkEmptyProcQ();
  currentProcess = NULL;
  deviceSema4 = 0;

  initPcbs();
  initASL();
  
  /* instantiate 1 process:
      be in kernal mode
      enable interrupts
      use program counter to set address of test
      set stack pointer to RAMTOP
      increment processCount (processCount++)
      call allocPcb in pcb.c to set process tree fields to NULL
      p_time = 0;
      p_semAdd = NULL;
      p_supportStruct = NULL;
      then call insertProcQ
      then call scheduler() */


  processCount = 0;
  softBlockedCount = 0;
  readyQueue = mkEmptyProcQ();
  currentProcess = NULL;
  deviceSema4 = 0;

  /*
  instantiate 1 process
  in kernal mode
  interrupts enabled
  pc p1test
  sp last and of ram
  processCount++;
  insertProcQ();
  scheduler();
  */


}


generalExpectionHandler(){
  /*
  Look at cause register stored by BIOS
  Multiway branch
  -interrupts
  -SYSCALL
  -programException
  -memoryManagment
  */
}
