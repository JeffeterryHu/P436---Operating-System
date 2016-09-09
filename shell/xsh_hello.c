// xsh_hello.c
// created by Shichao Hu
// created on 9/6/2016
// part of HW1

#include <xinu.h>
#include <stdio.h>
#include <string.h>

shellcmd xsh_hello(int nargs, char *args[]){
	
	char ss[50];
	scanf(" %s", ss);

	if (ss != "\0"){
		printf("%s, Welcome to the world of Xinu!!\n", ss);
	}else{
	printf("Sorry, wrong entry.");
	}
	return 0;
}
