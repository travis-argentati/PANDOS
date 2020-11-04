#ifndef CONSTS
#define CONSTS

/****************************************************************************
 *
 * This header file contains utility constants & macro definitions.
 *
 ****************************************************************************/

/* Hardware & software constants */
#define PAGESIZE		  4096			/* page size in bytes	*/
#define WORDLEN			  4				  /* word size in bytes	*/


/* timer, timescale, TOD-LO and other bus regs */
#define RAMBASEADDR		0x10000000
#define RAMBASESIZE		0x10000004
#define TODLOADDR		  0x1000001C
#define INTERVALTMR		0x10000020
#define TIMESCALEADDR	0x10000024

/* Size of Process Queue */
#define MAXPROC       20

/* utility constants */
#define	TRUE			    1
#define	FALSE			    0
#define HIDDEN			  static
#define EOS				    '\0'

#define NULL 			    ((void *)0xFFFFFFFF)

/* device interrupts */
#define DISKINT			  3
#define FLASHINT 		  4
#define NETWINT 		  5
#define PRNTINT 		  6
#define TERMINT			  7


#define DEVINTNUM		  5		  /* interrupt lines used by devices */
#define DEVPERINT		  8		  /* devices per interrupt line */
#define DEVREGLEN		  4		  /* device register field length in bytes, and regs per dev */
#define DEVREGSIZE	  16 		/* device register size in bytes */
#define DEVCOUNT      40    /* device count */

/* device register field number for non-terminal devices */
#define STATUS			  0
#define COMMAND			  1
#define DATA0			    2
#define DATA1			    3

/* device register field number for terminal devices */
#define RECVSTATUS  	0
#define RECVCOMMAND 	1
#define TRANSTATUS  	2
#define TRANCOMMAND 	3

/* device common STATUS codes */
#define UNINSTALLED		0
#define READY			    1
#define BUSY			    3

/* device common COMMAND codes */
#define RESET			    0
#define ACK				    1

/* Memory related constants */
#define KSEG0           0x00000000
#define KSEG1           0x20000000
#define KSEG2           0x40000000
#define KUSEG           0x80000000
#define RAMSTART        0x20000000
#define BIOSDATAPAGE    0x0FFFF000
#define	PASSUPVECTOR	  0x0FFFF900
#define BUSREGISTER     0x1000001C
#define BASEADD         0x10000054



/* Exceptions related constants */
#define	PGFAULTEXCEPT	  0
#define GENERALEXCEPT	  1

#define CAUSESHIFT    2
#define IOINTERRUPTS  0
#define TLBINVLDS     3
#define SYSEXCEPT     8
#define ALLOFF        0x00000000
#define INTERRUPTENABLED_P 0x00000004
#define IMON          0x0000FF00
#define TEON          0x08000000
#define INTERRUPTENABLED_C  0x00000001

/* Syscall related constants */
#define CREATEPROCESS   1
#define TERMPROCESS     2
#define PASSEREN        3
#define VERHOGEN        4
#define IOWAIT          5
#define GETTIME         6
#define CLOCKWAIT       7
#define GETSUPPORTDATA  8


#define PROCESSORLOCALTIMER 1
#define INTERVALTIMER       2

#define USERMODE_P  0x00000008

/* operations */
#define	MIN(A,B)		((A) < (B) ? A : B)
#define MAX(A,B)		((A) < (B) ? B : A)
#define	ALIGNED(A)		(((unsigned)A & 0x3) == 0)

/* Macro to load the Interval Timer */
#define LDIT(T)	((* ((cpu_t *) INTERVALTMR)) = (T) * (* ((cpu_t *) TIMESCALEADDR)))

/* Macro to read the TOD clock */
#define STCK(T) ((T) = ((* ((cpu_t *) TODLOADDR)) / (* ((cpu_t *) TIMESCALEADDR))))

#define RAMTOP(T) ((T) = ((* ((int *) RAMBASEADDR)) + (* ((int *) RAMBASESIZE))))

#endif
