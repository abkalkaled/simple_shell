#include "shell.h"
/**
 * handle_builtin - builtin
 * @cd: builtin command
 * Return: function pointer
 */
int (*handle_builtin(char *cd))(_shell *)
{
	_builtin builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "cd", cd_shell },
		{ "help", get_help },
	};
	int x;

	for (x = 0; builtin[x].det; x++)
	{
		if (_strcmp(builtin[x].det, cd) == 0)
			break;
	}
	return (builtin[x].f);
}
