/* process_ring file
 * created by Shichao Hu
 * created on 9/9/2016
 * part of assignment2
 * worked with Xiaohui Wang, he guided me through the work */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this version of counting_down doesn't work, only prints one value
void counting_down(int current_proc, int round, int proc, int arr[], int pid[]){
	int current_round = 0;
	while(current_round < round){
		printf("Ring Element %d : Round %d : Value : %d\n", current_proc, current_round, arr[current_proc]);
		if(current_proc < proc - 1){
		  arr[current_proc + 1] = arr[current_proc] - 1;
		}
		else{
		  arr[0] = arr[current_proc] - 1;
		}
		if(current_proc < proc - 1){
		  resume(pid[current_proc + 1]);
		}
	}
}

shellcmd process_ring(int nargs, char *args[]){
	int32 value = 0;
	int32 proc = 4;
	int32 round = 5;
	if(nargs == 2){
	  if((strcmp(args[1], "-h", 3) == 0) || (strcmp(args[1], "-help", 6) == 0)){}
	}
	else{
		int i = 1;
	    	if(i < nargs){
	      		if((strcmp(args[i], "-p", 3) == 0) || (strcmp(args[i], "-processes", 11) == 0)){
				if(i + 1 < nargs){
					proc = atoi(args[i + 1]);
					i += 2;
				}
			}
			else if((strcmp(args[i], "-r", 3) == 0) || (strcmp(args[i], "-round", 7) == 0)){
				if(i + 1 < nargs){
					round = atoi(args[i + 1]);
					i += 2;
				}
			}
			else if((strcmp(args[i], "-v", 3) == 0) || (strcmp(args[i], "-version", 9) == 0)){
				if(i + 1 < nargs){
					if(strcmp(args[i], "work", 5) == 0){
						value = 0;
						i += 2;
					}
					else if(strcmp(args[i+1], "loop", 5) == 0){
						value = 1;
						i += 2;
					}
					else if(strcmp(args[i+1], "hang", 5) == 0){
						value = 2;
						i += 2;
					}
					else if(strcmp(args[i+1], "chaos", 6) == 0){
						value = 3;
						i += 2;
					}
				}
			}
			else{
				printf("Invalid command line input.\n");
			}
	/*
	for(proc = 0, proc < 4, proc++){
		printf("Ring Element %d : Round %d : Value : %d\n", proc, round, value);
		if(proc = 3){
			proc = 0;
			count++;
			value--;
		}
	}
	*/
	if(value == 0){
		int i = 0;
		int arr[proc*round*100];
		int pid[proc*round*100];
		arr[0] = proc*round;
		if(i < proc){
			pid[i] = create(counting_down, 1024, 20, "count_down", 5, i, round, proc, arr, pid);
			resume(pid[i]);
			i++;
		}
	}
		  return 0;
		}
	}
}