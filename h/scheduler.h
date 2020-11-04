#ifndef SCHEDULER
#define SCHEDULER




#include "../h/types.h"

extern void scheduler();
extern void transferState();
extern void contextSwitch(pcb_t *currentProc);
extern void prepareSwitch(pcb_t *currentProc, int timeSlice);


#endif
