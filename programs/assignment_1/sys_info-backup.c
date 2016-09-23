/* created by Shichao Hu
 * Assignment 1 */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	char s[] = "hello\n";

	if(pid < 0){
		fprintf(stderr, "Fork failed.\n");
		exit(-1);
	}else if(pid == 0){
		close(fd[0]);		
		write(fd[1], s, (strlen(s) + 1)); // send s through pipe
		printf("Child process, return from fork = %d\n", pid);
	}else{
		close(fd[1]); // parent process close pipe
		printf("Parent process, return from fork, child pid = %d\n", pid);
		printf("Parent finished.\n");
		wait(pid);
		exit(0);	
	}
	return 0;
}


