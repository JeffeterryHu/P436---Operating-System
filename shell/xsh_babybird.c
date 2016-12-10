/* xsh_babybird.c */
/* Created by Shichao Hu */
/* Created on 9/29/2016 */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

mutex_t lock;
cond_t time_to_fetch;
cond_t dish_empty;
int babybird,eats,refill,worm_num,round = 0;

void BabyBirdEat(int which_baby, int currently_eaten){
  while(1){
    int currently_eaten = 0;
    mutex_lock(&lock);
    cond_wait(&dish_empty, &lock);
    worm_num -= 1;
    currently_eaten ++;
    kprintf("Baby bird %d ate a worm! (%d total)\n", which_baby, currently_eaten);

    if(worm_num == 0){
      cond_signal(&time_to_fetch);
    }
    else{
      cond_signal(&dish_empty);
    }

    if(round + 1 < babybird){
      round += 1;
    }
    else{
      round = 0;
    }
    mutex_unlock(&lock);

    //exit the progam when eaten = eats
    if(currently_eaten == eats){
      break;
    }
  }
  return;
}

void ParentFetch(int num_of_fetch){
  while(1){
    mutex_lock(&lock);
    cond_wait(&time_to_fetch, &lock);
    //the following if states will make sure the program will exit properly
    if(num_of_fetch == ((babybird*eats)%refill != 0) + (babybird*eats)/refill){
      mutex_unlock(&lock);
      break;
    }
    worm_num = refill;
    num_of_fetch += 1;
    printf("Parent bird filled the dish with %d worms!\n", worm_num);
    cond_signal(&dish_empty);
    mutex_unlock(&lock);
  }
  return;
}

shellcmd xsh_babybird(int nargs, char *args[]){
  int num_baby_birds;
  int num_fetch_worms;
  int num_eat_worms;
  int bbs[num_baby_birds];
  int i = 0;
  //num_fetch_worms = refill;
  //num_eat_worms = eats;
  //num_baby_birds = babybird;

  refill = num_fetch_worms;
  eats = num_eat_worms;
  babybird = num_baby_birds;

  if(nargs == 2){
    if((strcmp(args[1], "-h", 3) == 0) || (strcmp(args[1], "--help", 7) == 0)){
      printf("This is the help menu\n");
      printf("Please choose the number of babybird, worms to fetch and number of worms\n");
      printf("Command format is: -b num, -e num, -f num (order doesn't matter)\n");
      printf("Or --babies num, --eat num, --fetch num\n");
    }
  }
  else if(nargs == 7){
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

  mutex_create(&lock);
  cond_init(&dish_empty, 1);
  cond_init(&time_to_fetch, 0);
  while(i < num_baby_birds){
    bbs[i] = create(BabyBirdEat, 1024, 20, "babybird", 2, i, 0);
    resume(bbs[i]);
    i += 1;
  }
  resume(create(ParentFetch, 1024, 20, "parent", 1, 0));
  return 0;
}//end of function
