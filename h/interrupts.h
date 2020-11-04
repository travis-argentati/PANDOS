#ifndef INTERRUPTS
#define INTERRUPTS




#include "../h/types.h"

extern void interruptHandler();
extern void pltInterrupts(int lineNum);
extern void intervaltimerInterrupts(int lineNum);
extern void deviceInterrupts(int lineNum);
extern void flashInterrupts(int lineNum);
extern void networkInterrupts(int lineNum);
extern void printerInterrupts(int lineNum);
extern void terminalInterrupts(int lineNum);


#endif
