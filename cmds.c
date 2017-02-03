#include <unistd.h>
#include <string.h>
#include <stdio.h>

int cd(char** args);

int (*commands[])(char** args) = {
	&cd
};

char* commandLookup[] = {
	"cd"
};

int runcmd(char* cmd, char** args) {
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
