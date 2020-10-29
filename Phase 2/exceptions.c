#include "../h/const.h"
#include "../h/types.h"
#include "../h/asl.h"
#include "../h/pcb.h"



static int  mutex;


void SyscallHandler(int syscallRequest, int p_s, int p_supportStruct, int waitForTerminalRead){
  switch(s_a0/*whatever was in a0*/){
    case 1: int retValue = create_Process();
      break;
    case 2: terminate_Process();
      break;
    case 3: passeren();
      break;
    case 4: verhogen();
      break;
    case 5: wait_For_IO_Devices();
      break;
    case 6: get_CPU_Time();
      break;
    case 7: wait_For_Clock();
      break;
    case 8: get_Support_Data();
      break;

  }
}





void create_Process(){
  pcb_t *temp = allocPcb();
  processCount++;
  //Copy the state pointed at by a1(address of a process state) into temp -> p_s
  temp -> p_s = s_a1;
  //p_supportStruct from a2. If no parameter is provided, this field is set to NULL.
  temp -> p_supportStruct = s_a2;

  insertProcQ(&readyQueue, temp);
  insertChild(currentProcess, temp);
  temp -> p_time = 0;
  //Since this pcb/process is in "ready", not the blocked state
  temp -> p_semAdd = NULL;
  //put a return code in l0
  //return control to current process (LDST(& static is stored))
  LDST(temp);
}

void terminate_Process(){
  // While(currentProcess -> p_child != NULL){
  While(!emptyChild(currentProcess)){
    terminate_Process(removeChild(currentProcess));
  }
  outChild(currentProcess);
}

void passeren(){
  mutex--;
  if(mutex < 0){
    insertBlocked(&mutex, currentProcess);
    scheduler();
  }
  // LDST(return control to currentProcess)
  LDST(currentProcess -> p_s);
}

void verhogen(){
  mutex++;
  if(mutex <= 0){
    pcb_t *temp = removeBlocked(&mutex);
    insertProcQ(&readyQueue, temp);
  }
  LDST(currentProcess -> p_s);
}

/***** internal functions *****/

HIDDEN void passUpOrDie(int exceptType) {
  /*
  Function: passUpOrDie
  Purpose:
  Parameters: exceptType
  */

  if (curr_proc->p_supportStruct != NULL) {
    copyState ((state_PTR) BIOSDATAPAGE, &(curr_proc->p_supportStruct->sup_exceptState[exceptType])); /* something else goes at the end of this line potentially */
    LDCXT(curr_proc->p_supportStruct->sup_exceptContext[exceptType].c_stackPtr,
      curr_proc->p_supportStruct->sup_exceptContext[exceptType].c_status,
      curr_proc->p_supportStruct->sup_exceptContext[exceptType].c_pc);
  }
  abort_proc(curr_proc);
  switchProcess();
} /* end of passUpOrDie */

/***** external functions *****/

void pgmTrapHandler() {
  /*
  Function: pgmTrapHandler
  Purpose:
  Parameters: None
  */

  passUpOrDie(GENERALEXCEPT);
} /* end of pgmTrapHandler */

