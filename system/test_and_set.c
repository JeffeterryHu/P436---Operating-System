/* test_and_set */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall test_and_set(mutex_t* lock){
  intmask mask;
  mask = disable();
  mutex_t prev;
  prev = *lock;
  *lock = 1; //1 means lock is being held
  restore(mask);
  return(prev);
}
