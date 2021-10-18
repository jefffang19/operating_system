struct div_token{
	char **left, **right;
	int nleft, nright;
};
char ** parse(char *, int *);			/* turn string into tokens */
void free_argv(int, char **);		/* free argv array */
void run_command(int, char **, int);		/* func 1 run single-process command, 2 pipe two process, 3 >  , 4 < */
int is_background(int, char **); 	/* check for & at end */
int is_pipe(int size, char **argv); /* | */
int is_Rredirect(int size, char **argv); /* > */
int is_Lredirect(int size, char **argv); /* < */
struct div_token* divide_token(int, char **);  /* devide tokens into two sets (for piping or rederaction). Note that first argument should be num of original tokens, and second argument should be tokens*/

