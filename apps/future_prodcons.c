#include <future.h>
#include <xinu.h>

uint cons() {
  /*
  int i, status;
  status = future_get(f, &i);
  if (status < 1) {
    printf("failed\n\r");
      return -1;
  }
  printf("consumed: %d\n\r", i);
  return OK;
  */
}

uint prod() {
  /*
		int i, j;
		j = (int)f;
		for (i=0; i<1000; i++) {
				j += i;
		}
    printf("produced:%d\n\r",j);
		future_set(f, &j);
		return OK;
    */
}
