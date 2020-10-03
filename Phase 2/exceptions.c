#include "../h/const.h"
#include "../h/types.h"
#include "../h/asl.h"
#include "../h/pcb.h"


SyscallHandler(){
  switch(/*whatever was in a0*/){
    case 1: create_Process();
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
  temp -> p_s = ;
  insertProcQ(&readyQueue, temp);
  insertChild(currentProcess, temp);
  //put a return code in l0
  //return control to current process (LDST(& static is stored))

void terminate_Process(){


}

}
