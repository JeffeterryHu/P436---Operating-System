/* process_ring file
 * created by Shichao Hu
 * created on 9/9/2016
 * part of assignment2 */

#include <stdio.h>
#include <string.h>

shellcmd process_ring(int args, char *argv[]){
	int value;
	int proc;
	int round = 0;
	int count = 0;
	int n;	
	int m;

	while(1){
		printf("Number of processes : %d\n");
		scanf("%d", &n);
		printf("Number of rounds : %d\n");
		scanf("%d", &m); 
	}	
	
	for(proc = 0, proc < 4, proc++){
		printf("Ring Element %d : Round %d : Value : %d\n", proc, round, value);
		if(proc = 3){
			proc = 0;
			count++;
			value--;
		}
	}
	
	if(args ! = 2){
		printf("Error!");
	}

		
	
}
