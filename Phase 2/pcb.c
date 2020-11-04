#include "../h/const.h"
#include "../h/types.h"
#include "../h/pcb.h"

static pcb_t *pcbFree_h;

/*Insert the elements pointed to by p onto the pcbFree list. */
void freePcb(pcb_t *p){
  pcb_t *temp = pcbFree_h;
  if(pcbFree_h == NULL){
    pcbFree_h = p;
    p -> p_next = NULL;
  } else {
  pcbFree_h = p;
  p -> p_next = temp;
  }
}

/* Return NULL if the pcbFree list is empty. Otherwise, remove an element from the pcbFree
list, provide initial values for ALL of the pcbs fields (i.e. NULL and/or 0) and then return
a pointer to the removed element.pcbs get reused, so it is important that no previous value
persist in a pcb when it gets reallocated. */
pcb_t *allocPcb(){
  if (emptyProcQ(pcbFree_h)){
    return NULL;
  } else {
    pcb_t *temp = pcbFree_h;
    pcbFree_h = temp -> p_next;
    temp -> p_next = NULL;
    temp -> p_prev = NULL;
    temp -> p_prnt = NULL;
    temp -> p_child = NULL;
    temp -> p_sibnext = NULL;
    temp -> p_sibprev = NULL;
    temp -> p_semAdd = NULL;
    return temp;
  }
}

/*  Initialize the pcbFree list to contain all the elements of the static array
of MAXPROC pcbs.This method will be called only once during data structure initialization. */
void initPcbs() {
  static pcb_t pcbTable[MAXPROC];
  pcbFree_h = mkEmptyProcQ();
  for(int i = 0; i < MAXPROC; i++) {
    freePcb(&pcbTable[i]);
  }
}

/* This method is used to initialize a variable to be tail pointer to a process queue.
Return a pointer to the tail of an empty process queue; i.e. NULL. */
pcb_t *mkEmptyProcQ(){
  return NULL;
}

/* Return TRUE if the queue whose tail is pointed to by tp is empty.Return FALSE otherwise. */
int emptyProcQ(pcb_t *tp){
  return (tp == NULL);
}

/* Insert the pcb pointed to by p into the process queue whose tail-pointer is pointed to by tp.
Note the double indirection through tp to allow for the possible updating of the tail pointer as well. */
void insertProcQ(pcb_t **tp, pcb_t *p){
  if(emptyProcQ(*tp)){
    p -> p_next = p;
    p -> p_prev = p;
    (*tp) = p;
  } else {
    p -> p_prev = (*tp);
    p -> p_next = (*tp) -> p_next;
    p -> p_next -> p_prev = p;
    (*tp) -> p_next = p;
    (*tp) = p;
  }
}

/* Remove the first (i.e. head) element from the process queue whose tail-pointer is pointed to by tp.
Return NULL if the process queue was initially empty; otherwise return the pointer to the removed element.
Update the process queue's tail pointer if necessary. */
pcb_t *removeProcQ(pcb_t **tp){
  if(emptyProcQ(*tp)){
    return NULL;
  } else {
    if(headProcQ(*tp) == (*tp)) {
      pcb_t *temp = (*tp) -> p_next;
      temp -> p_prev -> p_next = temp -> p_next;
      (*tp) = NULL;
      return temp;
    }
    pcb_t *temp = (*tp) -> p_next;
    (*tp) -> p_next = temp -> p_next;
    temp -> p_next -> p_prev = (*tp);
    temp -> p_prev = temp -> p_next = NULL;
    return temp;
  }
}

/*  */
int searchforPcb(pcb_t **tp, pcb_t *p){
  pcb_t *temp = (*tp);
  pcb_t *endTemp = (*tp);
  while(temp -> p_next != p){
    if(temp -> p_next == endTemp){
      return FALSE;
    }
    temp = temp -> p_next;
  }
  return TRUE;
}

/* Remove the pcb pointed to by p from the process queue whose tail-pointer is pointed to by tp.
Update the process queue's tail pointer if necessary.  If the desired entry is not in the indicated
queue (an error condition), return NULL; otherwise, return p. Note that p can point to any element of
the process queue. */
pcb_t *outProcQ(pcb_t **tp, pcb_t *p){

  if(emptyProcQ((*tp))){
    return NULL;
  }
  if((*tp) == p){
    return removeProcQ(tp);
  }
  pcb_t *tpTemp = (*tp);
  while(tpTemp -> p_next != (*tp)){
    if(tpTemp -> p_next == p){
      pcb_t *temp = p;
      temp -> p_next -> p_prev = temp -> p_prev;
      temp -> p_prev -> p_next = temp -> p_next;
      temp -> p_prev = temp -> p_next = NULL;
      return temp;
    } else {
      tpTemp = tpTemp -> p_next;
    }
  }
  return NULL;

}

/* Return a pointer to the first pcb from the process queue whose tail is pointed to by tp.
Do not remove this pcb from the process queue. Return NULL if the process queue is empty. */
pcb_t *headProcQ(pcb_t *tp){
  if(emptyProcQ(tp)){
    return NULL;
  }
  return (tp -> p_next);
}

/* Return TRUE if the pcb pointed to by p has no children. Return FALSE otherwise. */
int emptyChild(pcb_t *p){
  return (p -> p_child == NULL);
}

/* Make the pcb pointed to by p a child of the pcb pointed to by prnt.*/
void insertChild(pcb_t *prnt, pcb_t *p){
  if(emptyChild(prnt)){
    prnt -> p_child = p;
    p -> p_prnt = prnt;
    p -> p_sibprev = NULL;
    p -> p_sibnext = NULL;
  } else {
    p -> p_prnt = prnt;
    p -> p_sibprev = prnt -> p_child;
    p -> p_sibprev -> p_sibnext =  p;
    p -> p_prnt -> p_child = p;
  }
}

/* Make the first child of the pcb pointed to by p no longer a child of p.  Return NULL if initially
 there were no children of p.  Otherwise,return a pointer to this removed first child pcb. */
pcb_t *removeChild(pcb_t *p){
  if(emptyChild(p)){
    return NULL;
  }
  if(p -> p_child -> p_sibprev == NULL){
    pcb_t *temp = p -> p_child;
    p -> p_child = NULL;
    return temp;
  }
  pcb_t *temp = p -> p_child;
  temp -> p_sibprev -> p_sibnext = NULL;
  temp -> p_prnt -> p_child = temp -> p_sibprev;
  temp -> p_prnt = temp -> p_sibprev = NULL;
  temp -> p_prnt = temp -> p_sibprev = NULL;
  return temp;
} 

/* Make the pcb pointed to by p no longer the child of its parent. If the pcb pointed to by p has
no parent, return NULL; otherwise, return p. Note that the element pointed to by p need not
be the first child of its parent. */
pcb_t *outChild(pcb_t *p){
  if(p -> p_prnt == NULL){
    return NULL;
  }
  if(p -> p_prnt -> p_child == p){
    return removeChild(p -> p_prnt);
  }
  if(p -> p_sibprev == NULL){
    p -> p_sibnext -> p_sibprev = NULL;
    p -> p_sibnext = p -> p_prnt = NULL;
    return p;
  }
  pcb_t *temp = p;
  p -> p_sibnext -> p_sibprev = p -> p_sibprev;
  p -> p_sibprev -> p_sibnext = p -> p_sibnext;
  p -> p_sibnext = p -> p_sibprev = p -> p_prnt = NULL;
  return temp;
}

