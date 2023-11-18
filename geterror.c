#include "shell.h"
/**
 * strcat_ - function that concatenat
 * @datashell: data relevant (directory)
 * @mssg: message to print
 * @err: error mssg
 * @str: lines
 * Return: error message
 */
char *strcat_(_shell *datashell, char *mssg, char *err, char *str)
{
	char *ifs;

	_strcpy(err, datashell->_argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, datashell->_args[0]);
	_strcat(err, mssg);
	if (datashell->_args[1][0] == '-')
	{
		ifs = malloc(3);
		ifs[0] = '-';
		ifs[1] = datashell->_args[1][1];
		ifs[2] = '\0';
		_strcat(err, ifs);
		free(ifs);
	}
	else
	{
		_strcat(err, datashell->_args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}
/**
 * error_get_cd - error message for cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd(_shell *datashell)
{
	int len, len_id;
	char *err, *str, *mssg;

	str = aux_itoa(datashell->count);
	if (datashell->_args[1][0] == '-')
	{
		mssg = ":Unaccpeted Option ";
		len_id = 2;
	}
	else
	{
		mssg = ": unable to change dir to ";
		len_id = _strlen(datashell->_args[1]);
	}

	len = _strlen(datashell->_argv[0]) + _strlen(datashell->_args[0]);
	len += _strlen(str) + _strlen(mssg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(str);
		return (NULL);
	}
	err = strcat_(datashell, mssg, err, str);
	free(str);
	return (err);
}

/**
 * error_not_seen - command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_seen(_shell *datashell)
{
	int len;
	char *err;
	char *str;

	str = aux_itoa(datashell->count);
	len = _strlen(datashell->_argv[0]) + _strlen(str);
	len += _strlen(datashell->_args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, datashell->_argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, datashell->_args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(str);
	return (err);
}
/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datashell: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_exit_shell(_shell *datashell)
{
	int len;
	char *err;
	char *str;

	str = aux_itoa(datashell->count);
	len = _strlen(datashell->_argv[0]) + _strlen(str);
	len += _strlen(datashell->_args[0]) + _strlen(datashell->_args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(err, datashell->_argv[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, datashell->_args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datashell->_args[1]);
	_strcat(err, "\n\0");
	free(str);

	return (err);
}
