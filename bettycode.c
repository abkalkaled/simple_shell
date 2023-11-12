#include "shell.h"
/**
 * main - Entry point of the program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	unsigned long max_pid;

	max_pid = (unsigned long)(1UL << (sizeof(unsigned long) * 8)) - 1;
	printf("Maximum PID: %lu\n", max_pid);
	return (0);
}
