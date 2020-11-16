#include "../h/const.h"
#include "../h/types.h"

/*#include "p2test.c"*/
#include "/usr/local/include/umps3/umps/libumps.h"

#include "../h/initial.h"
#include "../h/scheduler.h"
#include "../h/exceptions.h"
#include "../h/interrupts.h"
#include "../h/asl.h"
#include "../h/pcb.h"

int *mutex = 0;
int currentTOD;

void syscallHandler(/*int syscallRequest, int p_s, int p_supportStruct, int waitForTerminalRead*/){

  state_t *systemState = (state_t *) BIOSDATAPAGE;
  int currentSyscall = systemState -> s_a0;

  if(systemState -> s_status & USERMODE_P != 0){
    // Set the programTrap
    programTrapHandler();
  }

  transferState(systemState, &(currentProcess -> p_s));

  currentProcess -> p_s.s_pc = currentProcess -> p_s.s_pc + 4;

  switch(currentSyscall){
    case CREATEPROCESS: {
      create_Process();
    }

    case TERMPROCESS: {
      terminate_Process(currentProcess);
      scheduler();
    }

    case PASSEREN: {
      passeren();
    }

    case VERHOGEN: {
      verhogen();
    }

    case IOWAIT: {
      wait_For_IO_Devices();
    }

    case GETTIME: {

    }

    case CLOCKWAIT: {
      wait_For_Clock();
    }

    case GETSUPPORTDATA: {
      get_Support_Data();
    }

    // Case for when Syscall is not 1-8
    default: {
      passUpOrDie(GENERALEXCEPT);
    }


  }



}

void programTrapHandler(){
  passUpOrDie(GENERALEXCEPT);
}

void tlbTrapHandler(){
  passUpOrDie(PGFAULTEXCEPT);
}



void create_Process(){
  pcb_t *temp = allocPcb();

  if(temp == NULL) {
    /* fill v0 with -1. return */
    currentProcess -> p_s.s_v0 = -1;
    return;
  }

  //Copy the state pointed at by a1(address of a process state) into temp -> p_s
  transferState(&currentProcess -> p_s.s_a1, &temp -> p_s);
  //p_supportStruct from a2. If no parameter is provided, this field is set to NULL.
  support_t *supportData = currentProcess -> p_s.s_a2;
  if(supportData != NULL || supportData != 0) {
    temp -> p_supportStruct = supportData;
  }

  processCount++;
  insertProcQ(&readyQueue, temp);
  insertChild(currentProcess, temp);
  //Since this pcb/process is in "ready", not the blocked state
  //put a return code in v0
  currentProcess -> p_s.s_v0 = 1;
  //return control to current process (LDST(& static is stored))
  // contextSwitch(temp);
  contextSwitch(currentProcess);
}



void terminate_Process(pcb_t *currentProcess){
  while(!emptyChild(currentProcess)){
    terminate_Process(removeChild(currentProcess));
  }
  outChild(currentProcess);
}




void passeren(){

  mutex = (int *) currentProcess -> p_s.s_a1;
  *mutex--;
  if(*mutex < 0){
    blockCurrentProc(mutex);
  } else {
    contextSwitch(currentProcess);
  }
}

void verhogen(){

  mutex = (int *) currentProcess -> p_s.s_a1;
  *mutex++;
  if(*mutex <= 0){
    pcb_t *temp = removeBlocked(mutex);
    if(temp != NULL){
      insertProcQ(&readyQueue, temp);
    }
  }

  contextSwitch(currentProcess);

}


void passUpOrDie(int exceptionType){
  if(currentProcess -> p_supportStruct != NULL){
    transferState((state_t *) BIOSDATAPAGE, &(currentProcess -> p_supportStruct -> sup_exceptState[exceptionType]));
    LDCXT(currentProcess -> p_supportStruct -> sup_exceptContext[exceptionType].c_stackPtr,
          currentProcess -> p_supportStruct -> sup_exceptContext[exceptionType].c_status,
          currentProcess -> p_supportStruct -> sup_exceptContext[exceptionType].c_pc);
  }

  terminate_Process(currentProcess);
  scheduler();

}


void wait_For_IO_Devices(){

  int lineNumber = currentProcess -> p_s.s_a1;
  int deviceNumber = currentProcess -> p_s.s_a2;

  deviceNumber = deviceNumber + ((lineNumber - DISKINT) * DEVPERINT);

  if((lineNumber == TERMINT) && (currentProcess -> p_s.s_a3)){
    deviceNumber = deviceNumber + DEVPERINT;
  }

  deviceSema4[deviceNumber]--;

  if(deviceSema4[deviceNumber] < 0){
    softBlockedCount++;
    blockCurrentProc(&(deviceSema4[deviceNumber]));
  } else {
    currentProcess -> p_s.s_v0  = deviceStat[deviceNumber];
    contextSwitch(currentProcess);
  }
}

void get_CPU_Time(){

}

void blockCurrentProc(int *blockedSem){

  cpu_t stopTOD;
  STCK(stopTOD);

  currentProcess -> p_time = currentProcess -> p_time + (stopTOD - startTOD);
  insertBlocked(blockedSem, currentProcess);

  currentProcess = NULL;
  scheduler();

}

void wait_For_Clock(){

  clockSem--;

  if(clockSem < 0){
    softBlockedCount++;
    blockCurrentProc(&clockSem);
  }

  contextSwitch(currentProcess);

}

void get_Support_Data(){

}
