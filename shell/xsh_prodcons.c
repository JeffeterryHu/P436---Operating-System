/*
 * xsh_prodcons.c
 * Created by: Shichao Hu
 * Assignment 4
 */

#include <prodcons.h>
#include <future.h>
#include <xinu.h>

int n;
//semaphore p;
//semaphore c;

void rand_delay(int uS_max){
  sleep(rand()%uS_max);
}


shellcmd xsh_prodcons(int nargs, char *argv[]){

  if (nargs == 2 && strncmp(argv[1], "--help", 7) == 0){
    printf("Usage: %s [Integer] \n\n", argv[0]);
    printf("Instrcution:\n");
	  printf("\tCreates a producer and a consumer and Displays produced and consumed values on console\n");
    printf("Options:\n");
    printf("\t--help\tdisplay this help and exit\n");
    return OK;
  }
  /* Check for correct number of arguments */
  else if (nargs > 2){
    fprintf(stderr, "%s: too many arguments\n", argv[0]);
    fprintf(stderr, "Try '%s --help' for more information\n",
    argv[0]);
    return SYSERR;
  }
  else if (nargs < 1){
    fprintf(stderr, "%s: too few arguments\n", argv[0]);
    fprintf(stderr, "Try '%s --help' for more information\n", argv[0]);
    return SYSERR;
  }

  //create the process producer and consumer and put them in ready queue.
  //initialize semaphores:

  /*
  if(!use_future){
    c=semcreate(0);
    p=semcreate(1);

    resume( create(p, 1024, 20, "producer", 1, count) );
    resume( create(c, 1024, 20, "consumer", 1, count) );
  }
  */

  //future_t  *f1,  *f2,  *f3;
  //f1  =  future_alloc(0);
  //f2  =  future_alloc(0);
  //f3  =  future_alloc(0);
  //resume(  create(future_cons,  1024,  20,  "fcons1",  1,  f1)  );
  //resume(  create(future_cons,  1024,  20,  "fcons1",  1,  f1)  );
  //resume(  create(future_cons,  1024,  20,  "fcons2",  1,  f1)  );
  //resume(  create(future_cons,  1024,  20,  "fcons2",  1,  f1)  );
  //resume(  create(future_prod,  1024,  20,  "fprod3",  1,  f1)  );
  //resume(  create(future_prod,  1024,  20,  "fprod3",  1,  f1)  );
  //return OK;
}
