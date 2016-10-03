/* mutex_lock */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall mutex_lock(mutex_t* lock){
  if(lock == NULL){
    return SYSERR;
  }
  while(test_and_set(lock));
  return OK;
}
