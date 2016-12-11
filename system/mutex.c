/* mutex_lock */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>
typedef int mutex;
typedef int cond;

syscall mutex_lock(mutex_t* lock){
  if(lock != NULL){
    return SYSERR;
  }
  while(test_and_set(lock));
  return OK;
}

syscall mutex_unlock(mutex_t* lock){
  *lock = 0;
}

syscall mutex_create(mutex_t* lock){
  *lock = 0;
}

/*
syscall test_and_set(mutex *lock){
  intmask mask = disable();
  mutex pre = *lock;
  *lock = 1;
  restore(mask);
  return pre;
}

syscall cond_init(cond *cv, int v){
  *cv = v;
}

syscall cond_wait(cond *cv, mutex *lock){
  mutex_unlock(lock);
  while (test_and_set((mutex *) cv));
}

syscall cond_signal(cond *cv){
  *cv = 0;
}

*/

/*
syscall test_and_set_turn(cond *turn, int birdID){
    intmask mask = disable();
    int res = (*turn != birdID);
    restore(mask);
    return res;
    }

syscall turn_wait(cond *turn, int birdID){
     //mutex_unlock(lock);
     while (test_and_set_turn(turn, birdID));
     }
*/
