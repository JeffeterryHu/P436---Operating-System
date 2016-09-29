/* xsh_babybird.c */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

shellcmd xsh_babybird(int nargs, char *args[]){

  if(nargs == 2){
    if((strcmp(args[1], "-h", 3) == 0) || (strcmp(args[1], "--help", 6) == 0)){
      printf("HELP! HELP!");
    }
  }
  else{

  }
}
