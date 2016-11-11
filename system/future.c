/*  future.c file
 *  Assignment5
 *  Created By: Shichao Hu
 *  Created On: 11/10/2016
 */

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <future.h>
#include <future_prodcons.h>

future_t* future_alloc(future_mode_t mode){
  intmask mask;
  mask = disable();
  future_t* future = getmem(sizeof(future_t));
  if((future_mode_t*) mode == SYSERR){
    return NULL;
  }
  future->state = FUTURE_EMPTY;
  future->mode = mode;
  future->pid = NULL;
  future->value = malloc(int);
  future->get_queue = NULL;
  future->set_queue = NULL;
  restore(mask);
  return future;
}

  syscall future_free(future_t* f) {
    return freemem((char*)f, sizeof(f));
  }


  /* need to finish all the shared and queue */
  syscall future_get(future_t* f, int* value) {
    intmask mask = disable();
    if (f->state == FUTURE_READY) {
      *value = f->value;
      restore(mask);
      return OK;
    }
    if (f->state == FUTURE_EMPTY) {
      f->state = FUTURE_WAITING;
      f->pid = currpid;
      restore(mask);
      return SYSERR;
    }
  }

  syscall future_set(future_t* f, int value) {
    intmask mask;
    mask = disable();
    if (f->state == FUTURE_EMPTY) {
      f->value = *value;
      f->state = FUTURE_READY;
      restore(mask);
      return OK;
    }
    if (f->state == FUTURE_WAITING) {
      f->value = *value;
      f->state = FUTURE_READY;
      restore(mask);
      return OK;
    }
    if (f->state == FUTURE_SHARED)
    {

      restore(mask);
      return OK;
    }
    if (f->state == FUTURE_QUEUE)
    {
      restore(mask);
      return OK;
    }

    restore(mask);
    return SYSERR;
  }
}
