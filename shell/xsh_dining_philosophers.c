/*
  xsh_dining-philosophers.c

  Created by: Shichao Hu

  No team

  Collaborated with: Austin Hollett

  Assignment: Homework4

*/

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define THINK 0
#define HUNGRY 1
#define EATING 2
#define T "thinking"
#define H "hungry"
#define E "eating"

int num_of_phil, num_of_cycle, max_delay;
sid32 mutex;

void philosopher(int i, int *state[], sid32 *sem_state[], sid32 *mtx, int *done, int cycle, int delay);
void think(int delay);
void eat(int delay);
void forking(int i, sid32 mtx, int state[], sid32 sem_state[]);
void put_fork(int i, sid32 mtx, int state[], sid32 sem_state[]);
void test(int i, int state[], sid32 sem_state[]);
int left(int i);
int right(int i);

shellcmd xsh_dining_philosophers(int nargs, char *argv[]) {
  int i;
  if(nargs != 4) {
    kprintf("%s help\n", argv[0]);
    kprintf("%s <num of philosophers> <num  of cycles> <max delay>\n", argv[0]);
    return SYSERR;
  } else {
    for(i = 1; i < nargs; i++) {
      if (isdigit(*argv[i])) {
        switch(i) {
        case 1:
          num_of_phil = atoi(argv[i]);
          break;
        case 2:
          num_of_cycle = atoi(argv[i]);
          break;
        case 3:
          max_delay = atoi(argv[i]);
          break;
        }
      }
    }
  }
  int state[num_of_phil];
  int done = 0;

  mutex = semcreate(1);
  sid32 sid_phil[num_of_phil];
  for(i = 0; i < num_of_phil; i++)
    sid_phil[i] = semcreate(0);

  for(i = 0; i < num_of_phil; i++)
    resume(create(philosopher, 1024, 20, "philosopher", 10, i, &state, &sid_phil, &mutex, &done, num_of_cycle, max_delay));

  while(done != num_of_phil)
    sleepms(1);
  kprintf("fin\n");
  return OK;
}

void philosopher(int i, int *states[], sid32 *sem_states[], sid32 *mtx, int *done, int cycles, int delay) {
  int cycle_passed = 0;
  char *words;
  while(cycle_passed < cycles) {
    think(delay);
    switch(*states[i]) {
    case 0:
      words = "Thinking";
      break;
    case 1:
      words = "Hungry";
      break;
    case 2:
      words = "Eating";
      break;
    }

    forking(i, *mtx, *states, *sem_states);
    switch(*states[i]) {
    case 0:
      words = "Thinking";
      break;
    case 1:
      words = "Hungry";
      break;
    case 2:
      words = "Eating";
      break;
    }
    kprintf("Philsopher %d, %s, %d\n", i, words, cycle_passed);
    eat(delay);
    switch(*states[i]) {
    case 0:
      words = "Thinking";//forking
      break;
    case 1:
      words = "Hungry";
      break;
    case 2:
      words = "Eating";
      break;
    }
    put_fork(i, *mtx, *states, *sem_states);
    switch(*states[i]) {
    case 0:
      words = "Thinking";
      break;
    case 1:
      words = "Hungry";
      break;
    case 2:
      words = "Eating";
      break;
    }
    kprintf("Philsopher %d, %s, %d\n", i, words, cycle_passed);
    cycle_passed++;
  }
  *done += 1;
  return;
}

void think(int delay) { //delays with yields
  rand_delay(delay);
}

void eat(int delay) { //delays with yields
  rand_delay(delay);
}

void forking(int i, sid32 mtx, int states[], sid32 sem_states[]) { //test and set Hungry status
  wait(mtx);
  states[i] = HUNGRY;
  test(i, states, sem_states);
  signal(mtx);
  wait(sem_states[i]);
}

void put_fork(int i, sid32 mtx, int states[], sid32 sem_states[]) { //test and set think status and test left and right
  wait(mtx);
  states[i] = THINK;
  test(left(i), states, sem_states);
  test(right(i), states, sem_states);
  signal(mtx);
}

void test(int i, int states[], sid32 sem_states[]) {//tests if the philosopher isn't by an Eating philosopher
  if ((states[i] == HUNGRY) && (states[left(i)] != EATING) && (states[right(i)] != EATING)) {
    states[i] = EATING;
    signal(sem_states[i]);
  }
}

int left(int x) { //check left philosopher
  return x;
}

int right(int x) { //check right philosopher
  return (x+1) % num_of_phil;
}
