#include "shell.h"
/**
 * handle_sigint - Handle the crtl + c call in prompt
 * @sigint: Signal handler
 */
void handle_sigint(int sigint)
{
	(void)sigint;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
