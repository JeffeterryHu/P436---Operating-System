/* mutex_create */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall mutex_create(mutex_t* lock){
  *lock = 0;
}
