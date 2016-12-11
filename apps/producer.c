#include <prodcons.h>
#include <xinu.h>

void producer(int count){

  int produced_value = 0;
  int upperbound=count;
  int n;
  while(count>0){
    produced_value = upperbound - count;
    n = produced_value;
    //wait(produced);
    printf("Produced: %d\n", produced_value);
	  //signal(consumed);
    count--;
    sleep(455);
  }
}
