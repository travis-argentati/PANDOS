#include "../h/const.h"
#include "../h/types.h"
#include "../h/pcb.h"

/*HIDDEN pcb_t *pcbFree_h;*/
static pcb_t *pcbFree_h;

/*
void countPcbs() {
  pcb_t *temp = pcbFree_h;
  int count = 0;

  While(temp->p_next != NULL){}
    temp = temp->p_next;
    count++
  }
}
*/

/*pcbs which are no longer in use can be returned to the pcbFree list by usingthe method:*/

/*Insert the elements pointed to by p onto the pcbFree list. */
void freePcb(pcb_t *p){
  if(pcbFree_h == NULL){
    pcbFree_h = p;
    return;
  }
  pcb_t *temp = pcbFree_h;
  pcbFree_h = p;
  p -> p_next = temp;

}





/*pcbs should be allocated by using:*/

/*//codes
//if(pcbFree_h){
//return NULL;
//}*/


/* Return NULL if the pcbFree list is empty. Otherwise, remove an element from the pcbFree
list, provide initial values for ALL of the pcbs fields (i.e. NULL and/or 0) and then return
a pointer to the removed element.pcbs get reused, so it is important that no previous value
persist in a pcb when it gets reallocated. */
pcb_t *allocPcb(){
  if (emptyProcQ(pcbFree_h)){
    return NULL;
  } else {
    /*
    //Assign current head to a temp
    // The commented code below is old and I do not believe would work.
    // pcb_t *temp = removeProcQ(pcbFree_h);
    // temp -> p_next = NULL;
    // temp -> p_prev = NULL;
    // pcbFree_h -> p_next;
    */
    pcb_t *temp = pcbFree_h;
    pcbFree_h = temp -> p_next;
    temp -> p_next = NULL;
    return temp;
  }
}


/*To initialize the pcbFree List:*/

/*  Initialize the pcbFree list to contain all the elements of the static array
of MAXPROC pcbs.This method will be called only once during data structure initialization. */
void initPcbs() {
  static pcb_t pcbTable[MAXPROC];
  pcbFree_h = mkEmptyProcQ();
  for(int i = 0; i < MAXPROC; i++) {
    /*FreePcb(&pcbTable[i]);*/
    freePcb(&pcbTable[i]);
  }
}


/*2.2 Process Queue Maintenance



To  support  process  queues  there  should  be  the  following  externally  visiblefunctions:*/

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
    *tp = p;
  }
  /*//pcb_t *temp = NULL;*/
  p -> p_next = tp -> p_next;
  tp -> p_next = p;
  p -> p_prev = tp;
  p -> p_next -> p_prev = p;
  *tp = p;

}



/* Remove the first (i.e. head) element from the process queue whose tail-pointer is pointed to by tp.
Return NULL if the process queue was initially empty; otherwise return the pointer to the removed element.
Update the process queue's tail pointer if necessary. */
pcb_t *removeProcQ(pcb_t **tp){
  if(emptyProcQ(tp)){
    return NULL;
  } else {
    if(tp -> p_next == tp) {
      pcb_t* temp = tp;temp -> p_prev = temp -> p_next = NULL;
      tp = NULL;
      return temp;
    }
    pcb_t* temp;
    temp = tp -> p_next;
    tp -> p_next = temp -> p_next;
    temp -> p_next -> p_prev = tp;
    temp -> p_prev = temp -> p_next = NULL;
    /*//tp -> p_next = temp -> p_next;*/
    return temp;
  }
}





/* Remove the pcb pointed to by p from the process queue whose tail-pointer is pointed to by tp.
Update the process queue's tail pointer if necessary.  If the desired entry is not in the indicated
queue (an error condition), return NULL; otherwise, return p. Note that p can point to any element of
the process queue. */
pcb_t *outProcQ(pcb_t **tp, pcb_t *p){
  if(emptyProcQ(tp)){
    return NULL;
  }
  if((headProcQ(tp) == p) || (tp == p)){
    return removeProcQ(p);
  }
  pcb_t *temp = p;
  temp -> p_next -> p_prev = temp -> p_prev;
  temp -> p_prev -> p_next = temp -> p_next;
  temp -> p_prev = temp -> p_next = NULL;
  return temp;

}



/* Return a pointer to the first pcb from the process queue whose tailis pointed to by tp.
Do not remove this pcb from the process queue. Return NULL if the process queue is empty. */
pcb_t *headProcQ(pcb_t *tp){
  if(emptyProcQ(tp)){
    return NULL;
  }
  return (tp -> p_next);
}


/*2.3 Process Tree Maintenance



To support process trees there should be the following externally visible func-tions:*/
/* Return TRUE if the pcb pointed to by p has no children. Return FALSE otherwise. */
int emptyChild(pcb_t *p){
  return (p -> p_child == NULL);
}


/* Make the pcb pointed to by p a child of the pcb pointed to by prnt.*/
void insertChild(pcb_t *prnt, pcb_t *p){
  if(emptyChild(p)){
    prnt -> p_child = p;
    p -> p_prnt = prnt;
  }
  /*
  // Uncomment if siblings are singly linked
  // p -> p_prnt = prnt;
  // p -> p_sib = prnt -> p_child;
  // p -> p_prnt -> p_child = p;

  // Comment if siblings are doubly linked
  */
  p -> p_prnt = prnt;
  p -> p_sibprev = prnt -> p_child;
  p -> p_sibprev -> p_sibnext =  p;
  p -> p_prnt -> p_child = p;
}




/* Make the first child of the pcb pointed to by p no longer a child of p.  Return NULL if initially
 there were no children of p.  Otherwise,return a pointer to this removed first child pcb. */
pcb_t *removeChild(pcb_t *p){
  if(emptyChild(p)){
    return NULL;
  }
  /*
  // Below assumes sibling to the right is p_sibnext
  // pcb_t *temp = p -> p_child;
  // temp -> p_sibnext -> p_sibprev = NULL;
  // temp -> p_prnt -> p_child = temp -> p_sibnext;
  // temp -> p_prnt = temp -> p_sibnext = NULL;
  // return temp;

  //Below ssumes sibling to the right is p_sibprev
  */
  pcb_t *temp = p -> p_child;
  temp -> p_sibprev -> p_sibnext = NULL;
  temp -> p_prnt -> p_child = temp -> p_sibprev;
  p -> p_prnt = p -> p_sibprev = NULL;
  return p;

}




/* Make the pcb pointed to by p no longer the child of its parent. If the pcb pointed to by p has
no parent, return NULL; otherwise, return p. Note that the element pointed to by p need not
be the first child of its parent. */
pcb_t *outChild(pcb_t *p){
  if(p -> p_prnt == FALSE){
    return NULL;
  }
  if(p -> p_prnt -> p_child == p){
    return removeChild(p);
  }
  pcb_t *temp = p;
  temp -> p_sibnext -> p_sibprev = p -> p_sibprev;
  temp -> p_sibprev -> p_sibnext = p -> p_sibnext;
  p -> p_sibnext = p -> p_sibprev = p -> p_prnt = NULL;
  return p;

}
