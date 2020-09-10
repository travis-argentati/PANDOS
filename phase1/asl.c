#include "../h/const.h"
#include "../h/types.h"
#include "../h/asl.h"
#include "../h/pcb.h"




//Hidden asl_PTR semdFree_h

HIDDEN semd_t *semd_h,*semdFree_h;



/*To support the ASL there should be the following externally visible functions:*/
int insertBlocked(int *semAdd, pcb_t *p){
    /*
    given semAdd
    return p
    */
}
/* Insert the pcb pointed to by p at the tail of the process queue as-sociated
with the semaphore whose physical address is semAdd and set the semaphore
address of p to semAdd.  If the semaphore is cur-rently not active
(i.e. there is no descriptor for it in the ASL), allocate a new descriptor from
the semdFree list, insert it in the ASL (at the appropriate position),
initialize all of the fields (i.e.  set ssemAdd to semAdd, and s_procq to
mkEmptyProcQ()), and proceed as above.  If a new semaphore descriptor needs to
be allocated and the semdFree list is empty, return TRUE. In all other cases
return FALSE.*/


pcb_t *removeBlocked(int *semAdd){
    /*
    if (semAdd == NULL){
        return NULL;
    }
    head = NULL;
    return p;
    if (emptyProcQ(s_procq) == TRUE) {
        remove semaphore de-scriptor
    }
    return ?
    */
}
/*  Search  the  ASL  for  a  descriptor  of  this  semaphore.   If  none  is
found, return NULL; otherwise, remove the first (i.e. head) pcb from the
process  queue  of  the  found  semaphore  descriptor  and  return  a pointer
to it. If the process queue for this semaphore becomes empty(emptyProcQ(s_procq)
is  TRUE),  remove  the  semaphore  de-scriptor from the ASL and return it to
the semdFree list. */


pcb_t *outBlocked(pcb_t *p){
    /*
    if (p -> pcb does not exist) {
        return NULL;
    } else {
        remove p -> pcb
        return p;
    }
    */
}
/* Remove the pcb pointed to by p from the process queue associated with p’s
semaphore (p→p_semAdd) on the ASL. If pcb pointed to  by p does  not  appear  in
the  process  queue  associated  with p’s semaphore, which is an error condition,
return NULL; otherwise, re-turn p. */


pcb_t *headBlocked(int *semAdd){
    /*
    if (semAdd == NULL || semAdd is not found) {
        return NULL;
    }
    return p;
    */
}
/* Return a pointer to the pcb that is at the head of the process queue
associated with the semaphore semAdd. Return NULL if semAdd is not found on the
ASL or if the process queue associated with semAdd is empty. */


void initASL(){
    /* not sure what to do here */
}
/* Initialize the semdFree list to contain all the elements of the array
static semd_t semdTable[MAXPROC] This method will be only called once during
data structure initialization. */
