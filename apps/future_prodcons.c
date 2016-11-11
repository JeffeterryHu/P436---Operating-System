uint future_prod(future_t* fut) {
  int i, j;
  j = (int)fut;
  for (i = 0; i < 1000; ++i) {
    j += i;
  }
  future_set(fut, j);
  return OK;
}

uint future_cons(future_t* fut) {
  int i, status;
  status = (int)future_get(fut, &i);
  if (status < 1) {
    printf("future_get failed\n");
    return -1;
  }
  printf("it produced %d\n", i);
  return OK;
}
