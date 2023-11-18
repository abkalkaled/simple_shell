#include "shell.h"
/**
 * calls_error - calls error
 * @datashell: data structure that contains arguments
 * @err: value of erroe
 * Return: error
 */
int calls_error(_shell *datashell, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(datashell);
		break;
	case 126:
		error = error_path_126(datashell);
		break;
	case 127:
		error = error_not_found(datashell);
		break;
	case 2:
		if (_strcmp("exit", datashell->_args[0]) == 0)
			error = error_exit_shell(datashell);
		else if (_strcmp("cd", datashell->_args[0]) == 0)
			error = error_get_cd(datashell);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datashell->stat = err;
	return (err);
}
