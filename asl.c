#include "h/const.h"
#include "h/types.h"
#include "h/asl.h"
#include "h/pcb.h"


HIDDEN semd_t *semd_h,*semdFree_h;

/* This checks to see if semdFree_h is null and if it is, it sets semdFree_h's
s_next to null, otherwise s_next equals temp */
void freeSemd(semd_t *sem){
  semd_t *temp = semdFree_h;
  if(semdFree_h == NULL){
    semdFree_h = sem;
    semdFree_h -> s_next = NULL;
  } else {
  semdFree_h = sem;
  semdFree_h -> s_next = temp;
  }
}

/*  */
semd_t *allocSemd(){
  if(semdFree_h == NULL){
    return NULL;
  } else {
    semd_t *temp = semdFree_h;
    semdFree_h = temp -> s_next;
    temp -> s_next = NULL;
    temp -> s_procQ = mkEmptyProcQ();
    temp -> s_semAdd = NULL;
    return temp;
  }
}

/* Initialize the semdFree list to contain all the elements of the array
static semd_t semdTable[MAXPROC] */
void initASL(){
  static semd_t semdTable[MAXPROC+2];
  semdFree_h = NULL;

  semd_t *dummyMin = &(semdTable[0]);
  semd_t *dummyMax = &(semdTable[1]);

  dummyMin-> s_next = dummyMax;
  dummyMin -> s_procQ = mkEmptyProcQ();
  dummyMin -> s_semAdd = 0;
  semd_h = dummyMin;

  dummyMax -> s_next = NULL;
  dummyMax -> s_procQ = mkEmptyProcQ();
  dummyMax -> s_semAdd = 0x7FFFFFFF;

  for(int i = 2; i < MAXPROC+2; i++){
    freeSemd(&semdTable[i]);
  }
}

/* This function looks at semd_h's s_next and continues to move down the asl
until temp is no longer smaller than semAdd */
semd_t *traverseASL(int *semAdd){
  semd_t *temp = semd_h;

  while(temp -> s_next -> s_semAdd < semAdd){
    temp = temp -> s_next;
  }
  return temp;
}

/* Return a pointer to the pcb that is at the head of the process queue
associated with the semaphore semAdd. Return NULL if semAdd is not found on the
ASL or if the process queue associated with semAdd is empty. */
pcb_t *headBlocked(int *semAdd){
  semd_t *temp = traverseASL(semAdd);

  if((temp == NULL) || (emptyProcQ(temp -> s_next -> s_procQ))){
    return NULL;
  }

  return headProcQ(temp -> s_next -> s_procQ);
}

/* Insert the pcb pointed to by p at the tail of the process queue associated
with the semaphore whose physical address is semAdd and set the semaphore
address of p to semAdd.  If the semaphore is currently not active
(i.e. there is no descriptor for it in the ASL), allocate a new descriptor from
the semdFree list, insert it in the ASL (at the appropriate position),
initialize all of the fields (i.e.  set s_semAdd to semAdd, and s_procq to
mkEmptyProcQ()), and proceed as above.  If a new semaphore descriptor needs to
be allocated and the semdFree list is empty, return TRUE. In all other cases
return FALSE.*/
int insertBlocked(int *semAdd, pcb_t *p){
  semd_t *tempsemd = traverseASL(semAdd);

  if(tempsemd -> s_next -> s_semAdd == semAdd){
    p -> p_semAdd = semAdd;
    insertProcQ(&tempsemd -> s_next -> s_procQ, p);
    return FALSE;
  } else {
    semd_t *newSemd = allocSemd();
    if((newSemd == NULL)){
      return TRUE;
    }
    p -> p_semAdd = semAdd;
    newSemd -> s_semAdd = semAdd;
    newSemd -> s_procQ = mkEmptyProcQ();

    semd_t *temp = traverseASL(semAdd);

    newSemd -> s_next = temp -> s_next;
    temp -> s_next = newSemd;
    insertProcQ(&newSemd -> s_procQ, p);

    return FALSE;
  }
}

/*  Search  the  ASL  for  a  descriptor  of  this  semaphore.   If  none  is
found, return NULL; otherwise, remove the first (i.e. head) pcb from the
process  queue  of  the  found  semaphore  descriptor  and  return  a pointer
to it. If the process queue for this semaphore becomes empty(emptyProcQ(s_procq)
is  TRUE),  remove  the  semaphore  descriptor from the ASL and return it to
the semdFree list. */
pcb_t *removeBlocked(int *semAdd){
  semd_t *tempsemd = traverseASL(semAdd);
  if(tempsemd -> s_next -> s_semAdd == semAdd){
    pcb_t *removedPcb = removeProcQ(&tempsemd -> s_next -> s_procQ);
    if(emptyProcQ(tempsemd -> s_next -> s_procQ)){
      semd_t *semdWithEmptyProcQ = tempsemd -> s_next;
      tempsemd -> s_next = semdWithEmptyProcQ -> s_next;
      semdWithEmptyProcQ -> s_next = NULL;
      semdWithEmptyProcQ -> s_semAdd = NULL;
      semdWithEmptyProcQ -> s_procQ = mkEmptyProcQ();
      freeSemd(semdWithEmptyProcQ);
    }
    return removedPcb;
  } else {
    return NULL;
  }
}

/* Remove the pcb pointed to by p from the process queue associated with p’s
semaphore (p→p_semAdd) on the ASL. If pcb pointed to by p does  not  appear  in
the  process  queue  associated  with p’s semaphore, which is an error condition,
return NULL; otherwise, return p. */
pcb_t *outBlocked(pcb_t *p){
  semd_t *tempsemd = traverseASL(p -> p_semAdd);
    pcb_t *outedPcb = outProcQ(&tempsemd -> s_next -> s_procQ, p);
    if(outedPcb == NULL){
      return NULL;
    }
    if(emptyProcQ(tempsemd -> s_next -> s_procQ)){
      semd_t *semdWithEmptyProcQ = tempsemd -> s_next;
      tempsemd -> s_next = semdWithEmptyProcQ -> s_next;
      semdWithEmptyProcQ -> s_next = NULL;
      semdWithEmptyProcQ -> s_semAdd = NULL;
      semdWithEmptyProcQ -> s_procQ = mkEmptyProcQ();
      freeSemd(semdWithEmptyProcQ);
    }
    return outedPcb;
}
