/*
  created by Shichao Hu
  worked with Austin
  part of assignment 6
*/

#include <xinu.h>

char *getstk6(uint32	nbytes){
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*prev, *curr;	/* Walk through memory list	*/
	struct	memblk	*fit, *fitprev; /* Record block that fits	*/

	mask = disable();
	if (nbytes == 0){
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* Use mblock multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	fit = NULL;
	fitprev = NULL;  /* Just to avoid a compiler warning */

	while (curr != NULL){			/* Scan entire list	*/
		if (curr->mlength >= nbytes) {	/* Record block address	*/
			fit = curr;
			fitprev = prev;
			break;
		}
		prev = curr;
		curr = curr->mnext;
	}

	if (fit == NULL){			/* No block was found	*/
		restore(mask);
		return (char *)SYSERR;
	}
	if (nbytes == fit->mlength) {		/* Block is exact match	*/
		fitprev->mnext = fit->mnext;
	} else {				/* Remove top section	*/
		fit->mlength -= nbytes;
		fit = (struct memblk *)((uint32)fit + fit->mlength);
	}
	memlist.mlength -= nbytes;
	restore(mask);
	return (char *)((uint32) fit + nbytes - sizeof(uint32));
}
