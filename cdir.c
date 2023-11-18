#include "shell.h"
/**
 * cdir - changes current directory
 * @datashell: data relevant
 * Return: 1
 */
int cdir(_shell *datashell)
{
	char *dir;
	int home, hhome, ddash;

	dir = datashell->_args[1];

	if (dir != NULL)
	{
		home = _strcmp("$HOME", dir);
		hhome = _strcmp("~", dir);
		ddash = _strcmp("--", dir);
	}

	if (dir == NULL || !home || !hhome || !ddash)
	{
		cd_home(datashell);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datashell);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		_cd(datashell);
		return (1);
	}

	cd_des(datashell);
	return (1);
}
