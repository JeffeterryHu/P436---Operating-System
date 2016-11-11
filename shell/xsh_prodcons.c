/*
 * xsh_prodcons.c
 *
 */
#include <stdlib.h>
#include <thread.h>
#include <prodcons.h>
#include <stdint.h>
#include <future.h>

int n;
//semaphore c, p ;
/*
 * Shell command (prodcons).
 * nargs  number of arguments in args array
 * args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_prodcons(int nargs, char *args[])
{


    /* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    {
        printf("Usage: %s [Integer] \n\n", args[0]);
        printf("Description:\n");
	printf("\tCreates a producer and a consumer and Displays produced and consumed values on console\n");
        printf("\tThis will make sure that produced values are consumed properly and we\n");
        printf("\tare running thread threads and producer is producing a contant value\n");
        printf("Options:\n");
        printf("\t--help\tdisplay this help and exit\n");
        return OK;
    }

    /* Check for correct number of arguments */
    if (nargs > 2)
    {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }
    if (nargs < 1)
    {
        fprintf(stderr, "%s: too few arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
    }

    future *f1, *f2, *f3;

    f1 = future_alloc(0);
    f2 = future_alloc(0);
    f3 = future_alloc(0);

    resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
    resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
    resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
    resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
    resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
    resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
    return OK;
}
