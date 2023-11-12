#include "shell.h"
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	while (1)
	{
		printf("simple_shell$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		       	printf("\n");
		break;
	}
	command[strcspn(command, "\n")] = '\0';
        pid_t pid = fork();

        if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		execlp(command, command, (char *)NULL);
	       	perror("execlp");
		exit(EXIT_FAILURE);
        }
	else
	{
            wait(NULL);
	}
    }
    return (0);
}

