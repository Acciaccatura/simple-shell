#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int cd(char** args);
int sysexit(char** args);
int about(char** args);

int (*commands[])(char** args) = {
	&cd,
	&sysexit,
	&about
};

char* commandLookup[] = {
	"cd",
	"sysexit",
	"about"
};

int runcmd(char* cmd, char* args[]) {
	for (int a = 0; a < sizeof(commandLookup)/sizeof(char*); a++) {
	//	printf("loopity, oh and also comparing %s against: %s\n", cmd, commandLookup[a]);
		if (strcmp(commandLookup[a], cmd) == 0) {
	//		printf("%s running...\n", commandLookup[a]);
			return (*commands[a])(args); 
		}
	}
	return -2;		
}

int cd(char** args) {
	int ret = chdir(args[1]);
	if (ret == -1) {
		printf("cd: Couldn't find path %s. We're sorry... we're sorry.", args[1]);
	}
	return ret;
}

int sysexit(char** args) {
	printf("goodbye\n");
	exit(0);
}

int about(char* args[]) {
	printf("William's shell. It's a simple one, but nonetheless a shell.\n");
	printf("%lu\n", sizeof(*args));
	if (sizeof(*args) > 1) {
		if (strcmp(args[1], ":)") == 0) {
			printf("Thanks for the smile ^_^\n");
		}
	}
	return 0;
}
