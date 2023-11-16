#include "shell.h"
/**
 * _cd - changes to the parent dir
 * @datashell: data environment
 * Return: Void
 */
void _cd(_shell *datashell)
{
	char wd[PATH_MAX];
	char *direct, *cp_wd, *cp_strtok_wd;

	getcwd(wd, sizeof(wd));
	cp_wd = _strdup(wd);
	set_env("OLDPWD", cp_wd, datashell);
	direct = datashell->_args[1];
	if (_strcmp(".", direct) == 0)
	{
		set_env("WD", cp_wd, datashell);
		free(cp_wd);
		return;
	}
	if (_strcmp("/", cp_wd) == 0)
	{
		free(cp_wd);
		return;
	}
	cp_strtok_wd = cp_wd;
	rev_string(cp_strtok_wd);
	cp_strtok_wd = _strtok(cp_strtok_wd, "/");
	if (cp_strtok_wd != NULL)
	{
		cp_strtok_wd = _strtok(NULL, "\0");

		if (cp_strtok_wd != NULL)
			rev_string(cp_strtok_wd);
	}
	if (cp_strtok_wd != NULL)
	{
		chdir(cp_strtok_wd);
		set_env("WD", cp_strtok_wd, datashell);
	}
	else
	{
		chdir("/");
		set_env("WD", "/", datashell);
	}
	datashell->stat = 0;
	free(cp_wd);
}
/**
 * cd_des - changes to des dir
 * @datashell: datadirectories)
 * Return: void
 */
void cd_des(_shell *datashell)
{
	char wd[PATH_MAX];
	char *direct, *cp_wd, *cp_direct;

	getcwd(wd, sizeof(wd));

	direct = datashell->_args[1];
	if (chdir(direct) == -1)
	{
		get_error(datashell, 2);
		return;
	}

	cp_wd = _strdup(wd);
	set_env("OLDPWD", cp_wd, datashell);

	cp_direct = _strdup(direct);
	set_env("WD", cp_direct, datashell);

	free(cp_wd);
	free(cp_direct);

	datashell->stat = 0;

	chdir(direct);
}

/**
 * cd_previous - changes to the previous directory
 * @datashell: datanviron)
 * Return: no return
 */
void cd_previous(_shell *datashell)
{
	char wd[PATH_MAX];
	char *l_wd, *l_oldwd, *cp_wd, *cp_oldwd;

	getcwd(wd, sizeof(wd));
	cp_wd = _strdup(wd);

	l_oldwd = _getenv("OLDPWD", datashell->_env);

	if (l_oldwd == NULL)
		cp_oldwd = cp_wd;
	else
		cp_oldwd = _strdup(l_oldwd);
	set_env("OLDPWD", cp_wd, datashell);

	if (chdir(cp_oldwd) == -1)
		set_env("WD", cp_wd, datashell);
	else
		set_env("WD", cp_oldwd, datashell);

	l_wd = _getenv("WD", datashell->_env);

	write(STDOUT_FILENO, l_wd, _strlen(l_wd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_wd);
	if (l_oldwd)
		free(cp_oldwd);

	datashell->stat = 0;

	chdir(l_wd);
}

/**
 * cd_home - changes to home directory
 * @datashell: data relevant (environ)
 * Return: void
 */
void cd_home(_shell *datashell)
{
	char *l_wd, *home;
	char wd[PATH_MAX];

	getcwd(wd, sizeof(wd));
	l_wd = _strdup(wd);

	home = _getenv("HOME", datashell->_env);

	if (home == NULL)
	{
		set_env("OLDPWD", l_wd, datashell);
		free(l_wd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datashell, 2);
		free(l_wd);
		return;
	}

	set_env("OLDPWD", l_wd, datashell);
	set_env("PWD", home, datashell);
	free(l_wd);
	datashell->stat = 0;
}
