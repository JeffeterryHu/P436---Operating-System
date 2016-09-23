/* xsh_hello.c - xsh_hello */
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

void sys_info(int nargs, char *args[]) {
	char *cmd = args[1];
	char read_cmd[20];
	int pid;
	int p[2];
	char path[20];
	strcpy(path, "/usr/bin/");
	if (pipe(p) == -1){
		printf("Failed to make pipe");
	}
	pid = fork();
	if (pid < 0){
		printf("Failed to fork");
	}	
	else if (pid == 0){
		/* child process */
		close(p[1]);
		read(p[0], read_cmd, strlen(cmd)+1);
		strcat(path, read_cmd);
		printf("Child PID=%d\n", pid);
		if (strcmp(read_cmd, "echo") == 0){
			execl(path, read_cmd, "Hello", " World!");
		}
		else{
			execl(path, read_cmd, 0, 0);
		}
	}
	else{ 
		/* parent process */
		close(p[0]);
		write(p[1], cmd, strlen(cmd)+1);
		printf("Parent PID=%d\n", pid);
		wait(pid);
	}
}

int main(int nargs, char *args[]){
	sys_info(nargs, args);
	return 0;
}
