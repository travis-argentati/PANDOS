#include "../h/const.h"
#include "../h/types.h"
#include "../h/asl.h"
#include "../h/pcb.h"



interruptHandler(){
 /* who interrupted?
 handle one interrupt at a time (highest priority)
    for this we need:
        line number (in cause register)
        which device it was (look at interrupting device's bit map) */
  
}
