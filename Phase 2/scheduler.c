#include "../h/const.h"
#include "../h/types.h"
#include "../h/asl.h"
#include "../h/pcb.h"




scheduler(){

    /* removeProcQ(ReadyQueue) -> currentProc
    load 5000 on the local timer
    LDST(currentProc -> p_s)
    if processCount == 0:
        HALT;
    if processCount > 0 && softBlockedCount > 0:
        enable interrupts
        WAIT;
    if processCount > 0 && softBlockedCount == 0:
        PANIC; */

}
