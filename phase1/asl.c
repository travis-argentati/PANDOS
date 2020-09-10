#include "h/const.h"
#include "h/types.h"
#include "h/asl.h"
#include "h/pcb.h"




//Hidden asl_PTR semdFree_h

HIDDEN semd_t *semd_h,*semdFree_h;



void freeSemd(semd_t *sem){
  semd_t *temp = semdFree_h;
  if(semdFree_h == NULL){
    semdFree_h = sem;
    sem -> s_next = NULL;
  } else {
  semdFree_h = sem;
  sem -> s_next = temp;
  }
}

semd_t *allocSemd(){
  if(semdFree_h == NULL){
    return NULL;
  } else {
    semd_t *temp = semdFree_h;
    semdFree_h = temp -> s_next;
    temp -> s_next = NULL;
    temp -> s_procQ = NULL;
    temp -> s_semAdd = NULL;
    return temp;
  }
}


void initASL(){
  static semd_t semdTable[MAXPROC];
  semdFree_h = NULL;
  for(int i = 0; i < MAXPROC; i++){
    freeSemd(&semdTable[i]);
  }
}

/*
pcb_t *headBlocked(int *semAdd){
  if(searchForSem(semAdd)){
    return NULL;
  }
  if(emptyProcQ(semAdd -> s_procQ)){
  }
  return semAdd -> s_procQ -> p_next;
  }
*/

int insertBlocked(int *semAdd, pcb_t *p){
  /*if(*/
  // This is setting tempsemd to the sem previous to the desired sem
  s_semAdd *tempsemd = traverseASL(semAdd);
  if(tempsemd -> s_next -> s_semAdd == semdAdd){
    insertProcQ(tempsemd -> s_next -> s_procQ, p);
  } else {
    semd_t *newSemd = allocSemd();
    newSemd -> s_semAdd = semAdd;
    
    s_semAdd *temp = traverseASL(newSemd);
    insertProcQ()
    /* allocate a sem from the free list */
    /* traverse until the semdAdd in that iteration is <= */
  }
  if(emptyProcQ(semAdd -> s_procQ)){
    semd_t *temp = semdFree_h;
    semdFree_h = temp -> s_next;
    temp -> s_procQ = mkEmptyProcQ();
    temp -> s_semAdd = semdAdd;
    return temp;
  }
  p -> p_semAdd = semAdd;
  insertProcQ(semAdd -> s_procQ, p);
  return FALSE;
}


int *traverseASL(int *semAdd){
  int *temp = semd_h -> s_next;
  if(emptyProcQ(temp -> s_next -> s_procQ == FALSE)){
    return temp;
  }
  while(temp < semAdd){
    if(temp -> s_next == NULL){
      break;
    }
    if(temp -> s_next >= semdAdd){
      return temp -> s_next;
    }
    temp = temp -> s_next;
  }
}



/*To support the ASL there should be the following externally visible functions:*/
/*
int insertBlocked(int *semAdd, pcb_t *p){

}*/
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

}
/*  Search  the  ASL  for  a  descriptor  of  this  semaphore.   If  none  is
found, return NULL; otherwise, remove the first (i.e. head) pcb from the
process  queue  of  the  found  semaphore  descriptor  and  return  a pointer
to it. If the process queue for this semaphore becomes empty(emptyProcQ(s_procq)
is  TRUE),  remove  the  semaphore  de-scriptor from the ASL and return it to
the semdFree list. */


pcb_t *outBlocked(pcb_t *p){

}
/* Remove the pcb pointed to by p from the process queue associated with p’s
semaphore (p→p_semAdd) on the ASL. If pcb pointed to  bypdoes  not  appear  in
the  process  queue  associated  with p’s semaphore, which is an error condition,
return NULL; otherwise, re-turn p. */

pcb_t *headBlocked(int *semAdd){

}
/* Return a pointer to the pcb that is at the head of the process queue
associated with the semaphore semAdd. Return NULL if semAdd is not found on the
ASL or if the process queue associated with semAdd is empty. */

/*
void initASL(){

}*/
/* Initialize the semdFree list to contain all the elements of the array
static semd_t semdTable[MAXPROC] This method will be only called once during
data structure initialization. */
