#ifndef PCB
#define PCB

/************************* PROCQ.H *****************************
*
*  The externals declaration file for the Process Control Block
*    Module.
*
*  Written by Mikeyg
*/

#include "../h/types.h"
/*
extern void freePcb (pcb_PTR p);
extern pcb_PTR allocPcb ();
extern void initPcbs ();

extern pcb_PTR mkEmptyProcQ ();
extern int emptyProcQ (pcb_PTR tp);
extern void insertProcQ (pcb_PTR *tp, pcb_PTR p);
extern pcb_PTR removeProcQ (pcb_PTR *tp);
extern pcb_PTR outProcQ (pcb_PTR *tp, pcb_PTR p);
extern pcb_PTR headProcQ (pcb_PTR tp);

extern int emptyChild (pcb_PTR p);
extern void insertChild (pcb_PTR prnt, pcb_PTR p);
extern pcb_PTR removeChild (pcb_PTR p);
extern pcb_PTR outChild (pcb_PTR p);
*/

extern void freePcb (pcb_t *p);
extern pcb_t *allocPcb ();
extern void initPcbs ();

extern pcb_t *mkEmptyProcQ ();
extern int emptyProcQ (pcb_t *tp);
extern void insertProcQ (pcb_t **tp, pcb_t *p);
extern pcb_t *removeProcQ (pcb_t **tp);
extern pcb_t *outProcQ (pcb_t **tp, pcb_t *p);
extern pcb_t *headProcQ (pcb_t *tp);

extern int emptyChild (pcb_t *p);
extern void insertChild (pcb_t *prnt, pcb_t *p);
extern pcb_t *removeChild (pcb_t *p);
extern pcb_t *outChild (pcb_t *p);

/***************************************************************/

#endif
