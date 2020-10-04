#include "../h/interrupts.h"
#include "../h/const.h"
#include "../h/types.h"
#include "../h/asl.h"
#include "../h/pcb.h"




interruptHandler(){

  /*
  Who interrupted me?
  What line number? It will be in the cause Register
  Which device?
=======
 /* who interrupted?
 handle one interrupt at a time (highest priority)
    for this we need:
        line number (in cause register)
        which device it was (look at interrupting device's bit map) */

  


}
