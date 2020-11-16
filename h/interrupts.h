#ifndef INTERRUPTS
#define INTERRUPTS




#include "../h/types.h"

extern void interruptHandler();
extern void pltInterrupts(cpu_t stopTOD);
extern void intervaltimerInterrupts();
extern void deviceInterrupts(int lineNum);
extern void flashInterrupts(int lineNum);
extern void networkInterrupts(int lineNum);
extern void printerInterrupts(int lineNum);
extern void terminalInterrupts(int lineNum);

// cpu_t stopTOD;

#endif
