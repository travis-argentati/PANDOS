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

  initPcbs();
  initASL();

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
