#include "shell.h"
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	char *token = strtok(input, " ");
	int arg_count = 0;
	
	while (1)
	{
		printf("simple_shell$ ");
		if (fgets(input, sizeof(input), stdin) == NULL)
			printf("\n");
		break;
	}
	input[strcspn(input, "\n")] = '\0';
	while (token != NULL && arg_count < MAX_ARGS - 1)
	{
		args[arg_count] = token;
		token = strtok(NULL, " ");
		arg_count++;
        }
	args[arg_count] = NULL;
	pid_t pid = fork();

        if (pid == -1)
		perror("fork");
	else if (pid == 0)
		execvp(args[0], args);
	perror("execvp");
	exit(EXIT_FAILURE);
       	else
		wait(NULL);
    return (0);
}

