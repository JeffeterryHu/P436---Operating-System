/* mutex_unlock */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall mutex_unlock(mutex_t* lock){
  *lock = 0;
}
