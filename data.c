#include "shell.h"
/**
 * free_data - frees data structure
 * @datastruct: data structure
 * Return: no return
 */
void free_data(data_shell *datastruct)
{
	unsigned int i;

	for (i = 0; datastruct->_envn[i]; i++)
	{
		free(datastruct->_envn[i]);
	}

	free(datastruct->_envn);
	free(datastruct->pid);
}
/**
 * init_data - Initialize data structure
 * @datastruct: data structure
 * @_argv: argument vector
 * Return: no return
 */
void init_data(data_shell *datastruct, char **_argv)
{
	unsigned int i;

	datastruct->input = NULL;
	datastruct->_argv = _argv;
	datastruct->args = NULL;
	datastruct->status = 0;
	datastruct->count = 1;

	for (i = 0; envn[i]; i++)
		;
	datastruct->_envn = malloc(sizeof(char *) * (i + 1));
	for (i = 0; envn[i]; i++)
		datastruct->_envn[i] = _strdup(envn[i]);
	datastruct->_envn[i] = NULL;
	datastruct->pid = _itoa(getpid());
}

/**
 * main - Entry point
 * @_argc: argument count
 * @_argv: argument vector
 * Return: 0 on success.
 */
int main(int _argc, char **_argv)
{
	void _argc;
	data_shell datastruct;

	signal(SIGINT, get_sigint);
	init_data(&datastruct, _argv);
	shell_loop(&datastruct);
	free_data(&datastruct);
	if (datastruct.status < 0)
		return (255);
	return (datastruct.status);
}

