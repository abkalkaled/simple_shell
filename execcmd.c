#include "shell.h"
/**
 * is_cdir - checks ":" if is in the current directory.
 * @path:  char pointer char.
 * @i: int pointer
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i = *i + 1;
	}
	if (path[*i])
		*i = *i + 1;
	return (0);
}
/**
 * _search - searches cmd
 * @cmd: command name
 * @_env: environment variable
 * Return: location of the command.
 */
char *_search(char *cmd, char **_env)
{
	char *path, *_path, *t_path, *dir;
	int len_dir, len_cmd, i;
	struct stat s;

	path = _getenv("PATH", _env);
	if (path)
	{
		_path = _strdup(path);
		len_cmd = _strlen(cmd);
		t_path = _strtok(_path, ":");
		i = 0;
		while (t_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &s) == 0)
					return (cmd);
			len_dir = _strlen(t_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, t_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &s) == 0)
			{
				free(_path);
				return (dir);
			}
			free(dir);
			t_path = _strtok(NULL, ":");
		}
		free(_path);
		if (stat(cmd, &s) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &s) == 0)
			return (cmd);
	return (NULL);
}

/**
 * _executable - determines ifmexecutable
 * @datashell: data struct
 * Return: 0 if is not an executable, other number if it does
 */
int _executable(_shell *datashell)
{
	struct stat s;
	int a;
	char *input;

	input = datashell->_args[0];
	for (a = 0; input[a]; a++)
	{
		if (input[a] == '.')
		{
			if (input[a + 1] == '.')
				return (0);
			if (input[a + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[a] == '/' && a != 0)
		{
			if (input[a + 1] == '.')
				continue;
			a++;
			break;
		}
		else
			break;
	}
	if (a == 0)
		return (0);

	if (stat(input + a, &s) == 0)
	{
		return (a);
	}
	calls_error(datashell, 127);
	return (-1);
}

/**
 * errorcheck - verifie user permission
 * @dir: destination directory
 * @datashell: data structure
 * Return: 1 if there is an error, 0 if not
 */
int errorcheck(char *dir, _shell *datashell)
{
	if (dir == NULL)
	{
		calls_error(datash, 127);
		return (1);
	}

	if (_strcmp(datashell->_args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			calls_error(datashell, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datashell->_args[0], X_OK) == -1)
		{
			calls_error(datashell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 * @datashell: data relevant (args and input)
 * Return: 1 on success.
 */
int exec_cmd(data_shell *datashell)
{
	pid_t pd;
	pid_t wd;
	int sit;
	int exe;
	char *dir;
	(void) wd;

	exe = _executable(datashell);;
	if (exe == 0)
	{
		dir = _search(datashell->_args[0], datashell->_env);
		if (check_error_cmd(dir, datash) == 1)
			return (1);
	}
	if (exe == -1)
		return(1);

	pd = fork();
	if (pd == 0)
	{
		if (exe == 0)
			dir = _search(datashell->_args[0], datashell->_env);
		else
			dir = datashell->_args[0];
		execve(dir + exe, datashell->_args, datashell->_env);
	}
	else if (pd < 0)
	{
		perror(datashell->_argv[0]);
		return (1);
	}
	else
	{
		do {
			wd = waitpid(pd, &sit, WUNTRACED);
		} while (!WIFEXITED(sit) && !WIFSIGNALED(sit));
	}

	datashell->stat = sit / 256;
	return (1);
}
