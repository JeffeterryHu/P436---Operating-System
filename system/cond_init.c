/* cond_init */
/* Created by Shichao Hu */
/* Created on 10/1/2016 */

#include <xinu.h>

syscall cond_init(cond_t* cv){
  *cv = 0;
}
