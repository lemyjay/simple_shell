#include "shell.h"

/**
 * setenv_command - Set or update an environment variable.
 *
 * @args: An array of command arguments.
 */
void setenv_command(char *args[])
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}
	if (setenv(args[1], args[2], 1) != 0)
		fprintf(stderr, "Failed to set environment variable\n");
}

/**
 * unsetenv_command - Remove an environment variable.
 *
 * @args: An array of command arguments.
 */
void unsetenv_command(char *args[])
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}
	if (unsetenv(args[1]) != 0)
		fprintf(stderr, "Failed to unset environment variable\n");
}

