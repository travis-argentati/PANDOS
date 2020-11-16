#ifndef INITIAL
#define INITIAL




#include "../h/types.h"
#include "/usr/local/include/umps3/umps/libumps.h"
/*#include "p2test.c"*/

extern void main();
extern void generalExpectionHandler();

int processCount;
int softBlockedCount;
pcb_t *currentProcess;
pcb_t *readyQueue;
cpu_t startTOD;
unsigned int deviceStat[DEVCOUNT+DEVPERINT];
int deviceSema4 [DEVCOUNT+DEVPERINT+1];
#define clockSem deviceSema4 [DEVCOUNT+DEVPERINT]

#endif
