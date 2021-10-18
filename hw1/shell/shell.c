#define INPUT_LEN 255

#include <stdio.h>
#include <string.h>
#include "shell.h"

int main() {
    char line[INPUT_LEN], pwd[INPUT_LEN];
    int token_n;
    char **myArgv;
    printf("Welcome to my shell!\n");
    getcwd(pwd,100);
    printf("[MYSHELL]: %s$ ",pwd); 
    while (fgets(line, INPUT_LEN, stdin)) {
        if (myArgv = parse(line,&token_n)) {  /* if input string not null */
        	if(strcmp(myArgv[0],"exit") == 0) break;
	        if(is_pipe(token_n,myArgv)) run_command(token_n,myArgv,2);
	        else if(is_Rredirect(token_n,myArgv)) run_command(token_n,myArgv,3);	
	        else if(is_Lredirect(token_n,myArgv)) run_command(token_n,myArgv,4);
	        else run_command(token_n,myArgv,1); /* one process */
        }
        getcwd(pwd,100);
        printf("[MYSHELL]: %s$ ",pwd); 
    }
    return 0;
}
