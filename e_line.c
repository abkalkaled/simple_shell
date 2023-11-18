#include "shell.h"
/**
 * exe_line - finds builtins and commands
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exe_line(_shell *datashell)
{
	int (*builtin)(_shell *datashell);

	if (datashell->_args[0] == NULL)
		return (1);

	builtin = handle_builtin(datashell->_args[0]);

	if (builtin != NULL)
		return (builtin(datashell));

	return (exec_cmd(datashell));
}
