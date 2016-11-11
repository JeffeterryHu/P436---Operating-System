/*
 * xsh_prodcons.c
 *
 */
#include <stdlib.h>
#include <thread.h>
#include <prodcons.h>
#include <stdint.h>
#include <string.h>
#include <future.h>

//semaphore c, p ;
/*
 * Shell command (prodcons).
 * nargs  number of arguments in args array
 * args   array of arguments
 * return OK for success, SYSERR for syntax error
 */

 semaphore produced;
 semaphore consumed;
 int n;

shellcmd xsh_prodcons(int nargs, char *args[]){
  uint8_t use_future = 0;
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    {
	      //printf("\tCreates a producer and a consumer and Displays produced and consumed values on console\n");
        printf("Help is not provided.\n");
        return OK;
    }

    /* Check for number of arguments */
    if (nargs > 3)
    {
        fprintf(stderr, "Too many arguments\n");
        fprintf(stderr, "Usage:\nprodcons <-f> <count: int>\n");
        return SYSERR;
    }

    else if (nargs == 3){
      if(strncmp(argv[1],"-f",20)==0){
        use_future = 1;
      }
      else{
        fprintf(stderr, "Invalid argument %s\n", args[0]);
        fprintf(stderr, "Usage:\nprodcons <-f> <count: int>\n");
        return SYSERR;
      }
      int count = atoi(args[2]);
      if(count == 0){
        fprintf(stderr,"Invalid argument %s, %d\n", args[2]);
        return SYSERR;
      }
    }

    else if(nargs == 2){
      if(strncmp(args[1],"-f",20)==0){
        use_future = 1;
      }
      if(!use_future){
        count = atoi(args[1]);
        if(count == 0){
          fprintf(stderr,"Invalid argument %s\n", args[1]);
          return SYSERR;
        }
      }
    }

    if(!use_future){
      consumed = semcreate(0);
      produced = semcreate(1);

      resume(create(producer,1024,20,"producer",1,count));
      resume(create(consumer,1024,20,"consumer",1,count));
    }
    else{
      future *f_exclusive, *f_shared, *f_queue;
      f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
      f_shared = future_alloc(FUTURE_SHARED);
      f_queue = future_alloc(FUTURE_QUEUE);

      resume(  create(future_cons,  1024,  20,  "fcons1",  1,  f_queue)  );
      resume(  create(future_cons,  1024,  20,  "fcons2",  1,  f_queue)  );
      resume(  create(future_cons,  1024,  20,  "fcons3",  1,  f_queue)  );
      resume(  create(future_cons,  1024,  20,  "fcons4",  1,  f_queue)  );
      resume(  create(future_prod,  1024,  20,  "fprod1",  1,  f_queue)  );
      resume(  create(future_prod,  1024,  20,  "fprod2",  1,  f_queue)  );
      resume(  create(future_prod,  1024,  20,  "fprod3",  1,  f_queue)  );
      resume(  create(future_prod,  1024,  20,  "fprod4",  1,  f_queue)  );

      future_free(f_exclusive);
      future_free(f_shared);
      future_free(f_queue);
    }
    return OK;
}
