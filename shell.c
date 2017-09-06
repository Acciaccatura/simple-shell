#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "cmds.h"

#ifndef MY_ALLOC
#define MY_ALLOC 32
#endif

//I can barely see comments in Vim.
char* readLine() {
	char c;
	char* str = malloc(MY_ALLOC);
	int alloc_mem = MY_ALLOC;
	int counter = 0;
	while (1) {
		c = getchar();
		if (counter > alloc_mem) {
			str = realloc(str, alloc_mem*2);
			alloc_mem*=2;
		}
		if (c == '\n' || c == EOF) {
			return str;
		}
		str[counter] = c;
		counter++;
	}
}

char** tokenize(char* werd) {
	char** retthis = malloc(sizeof(char*)*MY_ALLOC);
	int retsize = sizeof(char*)*MY_ALLOC;
	int rettc = 0;
	int werdc = 0;
	bool inquotes = false;
	bool isvaling = true;
	retthis[rettc] = &(werd[werdc]);
	rettc++;
	while (werd[werdc] != '\0') {
		if (werd[werdc] == ' ' && !inquotes) {
			werd[werdc] = '\0';
			isvaling = false;	
		} else if (werd[werdc] == '\"'){
			if (isvaling) {
				isvaling = false;
			}
			werd[werdc] = '\0';
			inquotes = !inquotes;
		} else if (!isvaling){
			isvaling = true;
			if (rettc*sizeof(char*) > retsize) {
				retsize *= 2;
				retthis = realloc(retthis, retsize);
			}
			retthis[rettc] = &(werd[werdc]);
			rettc++;
	//		printf("%d IS RETTC!!!!!!!!!!!!!!!!!!!!\n", rettc);
		}
		werdc++;
	}
	for (int a = 0; a < rettc/sizeof(char*); a++) {
		printf("%s, ", retthis[a]);
	}
	return retthis;
	/*
	char** retthis = malloc(sizeof(char*)*MY_ALLOC);
	int alloc_mem = MY_ALLOC;
	int counter = 0;
	if (werd != NULL) {
		//tokenize by '"'
		char* token = strtok(werd, " ");
		while (token != NULL) {
			if (counter > alloc_mem) {
				retthis = realloc(retthis, alloc_mem*2);
				alloc_mem*=2;
			}
			retthis[counter] = token;
			counter++;
			token = strtok(NULL, " ");
		}
		return retthis;
	} else return 0;
	*/
}

char* getdir() {
	char buff[1024];
	char* retthis = getcwd(buff, 1024);
	if (retthis != NULL) {
		return retthis;
	} else return NULL;
}

int executeprog(char** varargs) {
	pid_t prog = fork();
	int status;
	if (prog < 0) {
		perror("oh no");
		return -1;
	} else if (prog == 0) {
		if (execvp(*varargs, varargs) < 0) {
			perror(*varargs);
			exit(1);
		}
	} else {
		while(waitpid(-1, &status, WUNTRACED) != prog);
//		printf("parent stopped waiting for his kid");
		return 1;
	}
}

int execute(char** varargs) {
	int cmd_res = runcmd(*varargs, varargs);
	if (cmd_res == -1) {
		return executeprog(varargs);
	} else {
		return cmd_res;
	}
}

int main() {
	printf("William's Shell!\n");
	while (1) {
		char* cwd = getdir();
		printf("%s > ", cwd);
		char* str = readLine();
//		printf("[%s]\n", str);
		char** tokens = tokenize(str);
		execute(tokens);
	}
	return 0;
}
