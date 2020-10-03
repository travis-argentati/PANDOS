#include "/Phase 1/h/const.h"
#include "/Phase 1/h/types.h"
#include "/Phase 1/h/asl.h"
#include "/Phase 1/h/pcb.h"

processCount = 0;
softBlockedCount = 0;
readyQueue = mkEmptyProcQ();
currentProcess = NULL;
int deviceSema4 = 0;

void main(){

  initPcbs();
  initASL();



}
