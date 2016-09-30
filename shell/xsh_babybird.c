/* xsh_babybird.c */
/* Created by Shichao Hu */
/* Created on 9/29/2016 */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

shellcmd xsh_babybird(int nargs, char *args[]){
  int num_baby_birds;
  int num_fetch_worms;
  int num_eat_worms;

  if(nargs == 2){
    if((strcmp(args[1], "-h", 3) == 0) || (strcmp(args[1], "--help", 7) == 0)){
      printf("HELP! HELP!\n");
    }
  }
  else{
    int i = 1;
    while(i < nargs){
      if((strcmp(args[i], "-b", 3) == 0) || (strcmp(args[i], "--babies", 9)== 0)){
        if(i + 1 < nargs){
          num_baby_birds = atoi(args[i+1]);
          i += 2;
        }
      }
      else if((strcmp(args[i], "-e", 3) == 0) || (strcmp(args[i], "--eat", 6) == 0)){
        if(i + 1 < nargs){
          num_eat_worms = atoi(args[i+1]);
          i += 2;
        }
      }
      else if((strcmp(args[i], "-f", 3) == 0) || (strcmp(args[i], "--fetch", 8) == 0)){
        if(i + 1 < nargs){
          num_fetch_worms = atoi(args[i+1]);
          i += 2;
        }
      }
      else{
        printf("Invalid command line input by user.\n");
        break;
      }
    }
  }



  return 0;
}//end of function
