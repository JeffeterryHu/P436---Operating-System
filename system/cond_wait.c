/* cond_wait */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall cond_wait(cond_t* cv, mutex_t* lock){
  mutex_unlock(lock);
  while(test_and_set(lock));
}
