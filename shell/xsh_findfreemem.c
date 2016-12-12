/* Created by: Shichao Hu
 * get help from Austin
 * Part of Assignment 6
 */

#include <xinu.h>

shellcmd xsh_mem(int nargs, char *argv[]){

	struct memblk *curr;
	curr = memlist.mnext;

  if(nargs > 2){
    kprintf("Enter Correct output\n");
	  return SYSERR;
  }
  else {
    if(nargs == 2 && strncmp(argv[1], "--help", 7) == 0){
      printf("Use:\n");
		  printf("\t%s [command]\n", argv[0]);
		  printf("Description:\n");
		  printf("\tThis function will traverse through the free memory space and prints the address and length of each free block\n");
		  printf("\t--help\tdisplay this help and exit\n");
		  return OK;
    }
    else {
      while(curr!=NULL){
        printf("Length: %d Address: 0x%08x\n",curr->mlength,curr);
        curr = curr->mnext;
      }
    }
  }
  return OK;
}
