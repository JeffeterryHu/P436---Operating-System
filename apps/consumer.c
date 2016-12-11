#include <prodcons.h>
#include <xinu.h>

void consumer(int count){

  int consumed_value;
  int n;
  while(count>0){

    //wait(consumed);

    consumed_value = n;

    sleep(455);

    printf("Consumed: %d\n",consumed_value);

    //signal(produced);

    count--;
  }
}
