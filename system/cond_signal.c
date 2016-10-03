/* cond_signal */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall cond_signal(cond_t* cv){
  *cv = 1;
}
