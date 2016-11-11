#include  <stddef.h>
#include	<stdio.h>
#include  <future.h>
#include  <semaphore.h>

extern int n;
extern semaphore produced;
extern semaphore consumed;

void consumer(int count);
void producer(int count);

uint future_prod(future *fut);
uint future_cons(future *fut);
