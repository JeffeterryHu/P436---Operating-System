/*
  created by Shichao Hu
  worked with Austin
  part of assignment 6
*/

#include <xinu.h>

char *getmemNEW(uint32	nbytes){
	intmask	mask;			/* interrupt mask		*/
	struct	memblk	*prev, *curr, *leftover;

	mask = disable();
	if (nbytes == 0){
    restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL){			/* Search free list	*/
    if (curr->mlength >= nbytes){	/* check if exact match with block	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;
			restore(mask);
			return (char *)(curr);
		}
		else{			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
