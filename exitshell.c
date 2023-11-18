#include "shell.h"
/**
 * exit_ - exits shell
 * @datashell: relevant data
 * Return: 0
 */
int exit_(_shell *datashell)
{
	unsigned int det;
	int is_digit;
	int str_len;
	int big_num;

	if (datashell->_args[1] != NULL)
	{
		det = _atoi(datashell->_args[1]);
		str_len = _strlen(datashell->_args[1]);
		big_num = det > (unsigned int)INT_MAX;
		is_digit = _isdigit(datashell->_args[1]);
		if (!is_digit || str_len > 10 || big_num)
		{
			calls_error(datashell, 2);
			datashell->stat = 2;
			return (1);
		}
		datashell->stat = (det % 256);
	}
	return (0);
}
