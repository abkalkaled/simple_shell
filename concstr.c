#include "shell.h"
/**
 * _strcat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int i,j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{
	size_t t;

	for (t = 0; src[t] != '\0'; t++)
	{
		dest[t] = src[t];
	}
	dest[t] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string to locate from
 * @c: character to be searched
 * Return: the pointer to the first c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: first part
 * @a: bytes
 * Return: num of a
 */
int _strspn(char *s, char *a)
{
	int i, j, boolean;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		boolean = 1;
		for (j = 0; *(a + j) != '\0'; j++)
		{
			if (*(s + i) == *(a + j))
			{
				boolean = 0;
				break;
			}
		}
		if (boolean == 1)
			break;
	}
	return (i);
}
