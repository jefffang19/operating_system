#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/* Parse a commandline string into an argv array. Return num of tokens by pointer*/
char ** parse(char *line, int *num_token) {

  	static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv;

  	/* Nothing entered. */
  	if (line == NULL) {
    	return NULL;
  	}

  	/* Init strtok with commandline, then get first token.
     * Return NULL if no tokens in line.
     */
	token = strtok(line, delim);	
	if(token==NULL) return NULL;
	
	
  	/* Create array with room for first token.
	 */
	newArgv = malloc(sizeof(char *));
	newArgv[count] = malloc(sizeof(token));
	memcpy(newArgv[count],token,sizeof(token));
	++count;

  	/* While there are more tokens...
	 *
	 *  - Get next token.
	 *	- Resize array.
	 *  - Give token its own memory, then install it.
	 */
	do{
		token = strtok(NULL, delim);
		if(token==NULL) break;
		newArgv = (char*)realloc((void*)newArgv,sizeof(char*)* (count+1));
		newArgv[count] = malloc(sizeof(token));
		memcpy(newArgv[count],token,sizeof(token));
		++count;
	}while(token!=NULL);
	newArgv[count] = NULL; /* for execvp() to not have bug for some reason */
	*num_token = count; //return the number of tokens by pointer
  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(int size, char **oldArgv) {

	int i = 0;
	/* Free each string hanging off the array.
	 * Free the oldArgv array itself.
	 *
	 * Fill in code.
	 */
	 for(i;i < size;++i){
	 	free(oldArgv[i]);
	 }
	 free(oldArgv);
}

/*for debug purpose*/
/*
int main(){
	char input[100], **parsed;
	int n_token;
	fgets(input,100,stdin);
	parsed = parse(input, &n_token);
	int i=0;
	printf("num : %d\n",n_token);
	for(i;i < n_token;++i){
		printf("%s\n",parsed[i]);
	}
	free_argv(n_token,parsed);
	return 0;
}
*/
