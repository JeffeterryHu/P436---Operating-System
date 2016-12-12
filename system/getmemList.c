#include <xinu.h>
/*
int getmemList(){
  intmask mask;    //interrupt mask
  struct memblock *pre;
  struct memblock *curr

  mask = disable();
  pre = &memlist;
  curr = memlist.mnext;
  if(curr == NULL){
    printf("Exceeds memory");
    return -1;
  }

  while(curr != NULL){
    printf("Current memory block address is %u, and the length is %u\n", curr,curr->mlength");
    curr = curr->mnext;
  }
  restore(mask);
  return 0;
}
*/
