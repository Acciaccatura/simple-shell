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
		printf("loopity, oh and also comparing %s against: %s\n", cmd, commandLookup[a]);
		if (strcmp(commandLookup[a], cmd) == 0) {
			printf("%s running...\n", commandLookup[a]);
			return (*commands[a])(args); 
		}
	}		
}

int cd(char** args) {
	return chdir(args[1]);
}
