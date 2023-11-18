#include "shell.h"
/**
 * get_line - alocates line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @i: size of line
 * @j: size of buffer
 */
void get_line(char **lineptr, size_t *i, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*i = j;
		else
			*i = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*i < j)
	{
		if (j > BUFSIZE)
			*i = j;
		else
			*i = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * handle_line - Reads
 * @lineptr: buffer that stores the input
 * @i: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t handle_line(char **lineptr, size_t *i, FILE *stream)
{
	int j;
	static ssize_t input;
	ssize_t val;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		j = read(STDIN_FILENO, &t, 1);
		if (j == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	get_line(lineptr, i, buffer, input);
	val = input;
	if (j != 0)
		input = 0;
	return (val);
}
