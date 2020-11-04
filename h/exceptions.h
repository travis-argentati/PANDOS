#ifndef EXPCEPTIONS
#define EXCEPTIONS




#include "../h/types.h"

extern void syscallHandler(/*int syscallRequest, int p_s, int p_supportStruct, int waitForTerminalRead*/);
extern void programTrapHandler();
extern void tlbTrapHandler();
extern void create_Process();
extern void terminate_Process(pcb_t *currentProcess);
extern void passeren();
extern void verhogen();
extern void passUpOrDie(int exceptionType);
extern void wait_For_IO_Devices();
extern void get_CPU_Time();
extern void wait_For_Clock();
extern void get_Support_Data();
extern void blockCurrentProc(int *blockedSem);




#endif
