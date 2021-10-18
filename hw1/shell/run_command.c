#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h> /* STDIN_FILENO */
#include <fcntl.h> /* open() */
#include "shell.h"


/* func 1 run single-process command, 2 pipe two process, 3 > , 4 < */
void run_command(int num_token, char **myArgv, int func) {
    pid_t pid, pid2;
    int stat, stat2; /* status of ternimating process */ 
	int pipe_fd[2], rd_fd, file;
    struct div_token *a;
    /* Create a new child process.*/
	pid = fork();
	switch (pid) {
		/* Error. */
		case -1 :
			printf("fork 1 encountered error!\n");
			exit(EXIT_FAILURE);
		/* Parent. */
		default :
			/* background */
			if(is_background(num_token,myArgv))
				printf("child [PID]: %u\n",pid);
			/* wait for child */
			else waitpid(pid, &stat, 0);
			return;
		/* Child. */
		case 0 :
			switch (func) {
				case 1: /* run single process cmd */			
					execvp(myArgv[0], myArgv);
				break;
				case 2: /* pipe two process */	
					a = divide_token(num_token, myArgv);
					if(pipe(pipe_fd) < 0){
						printf("Pipe Failed\n");
						exit(EXIT_FAILURE);
					}
					pid2 = fork(); /* create a new child */
					switch (pid2) {
						case -1 :
							printf("fork 2 encountered error!\n");
							exit(EXIT_FAILURE);
						/* Parent. 
							read */
						default :
							/* wait for child */
							waitpid(pid2, &stat2, 0);
							close(pipe_fd[1]); /* close write */
						    dup2(pipe_fd[0],STDIN_FILENO);
							close(pipe_fd[0]);
							if (execvp(a->right[0],a->right) == -1){
						        printf("Error: \"%s\" command not found\n",myArgv[0]);
						        exit(EXIT_FAILURE);
						    }
						    break;
						/* Child. 
							write */
						case 0 :
							close(pipe_fd[0]); /* close read */
							dup2(pipe_fd[1],STDOUT_FILENO);
							close(pipe_fd[1]);
							if (execvp(a->left[0],a->left) == -1){
						        printf("Error: \"%s\" command not found\n",myArgv[0]);
						        exit(EXIT_FAILURE);
						    }
						    break;
					}
					break;
				case 3: /* > */
					a = divide_token(num_token, myArgv);
					rd_fd = open(a->right[0],O_CREAT|O_RDWR); /* can read and write */
					dup2(rd_fd,STDOUT_FILENO);  /* close stdout */
					close(rd_fd);
					if(execvp(a->left[0],a->left) == -1){
						printf("Error: \"%s\" command not found\n", myArgv[0]);
						exit(EXIT_FAILURE);
					}
					break;
				case 4: /* < */
					a = divide_token(num_token, myArgv);
					rd_fd = open(a->right[0],O_RDONLY);
					dup2(rd_fd,STDIN_FILENO); /* close stdin */
					close(rd_fd);
					if(execvp(a->left[0],a->left) == -1){
						printf("Error: \"%s\" command not found\n", myArgv[0]);
						exit(EXIT_FAILURE);
					}
					break;	
			}
			break;
	}
}

/* for debug purpose */
/*
int main(){
	//char *t[3] = {"echo","hello","&"};
	//run_command(3,t,1);
	//char *test[4] = {"xargs","echo","<","test.txt"};
	//run_command(4,test,4);
	char *testpipe[7] = {"ls","|","xargs","cat",NULL};
	run_command(4,testpipe,2);
	return 0;
}
*/
