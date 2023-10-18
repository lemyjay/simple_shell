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

/**
 * handle_cd_command - change the current directory of the process.
 *
 * @args: an array of arguments containing the directory to change to.
 */
void handle_cd_command(char *args[])
{
	char *new_directory, *current_directory;

	if (args[1] == NULL || _strcmp(args[1], "~") == 0)
		new_directory = getenv("HOME");
	else if (_strcmp(args[1], "-") == 0)
		new_directory = getenv("OLDPWD");
	else
		new_directory = args[1];

	current_directory = getcwd(NULL, 0);

	if (chdir(new_directory) == 0)
	{
		setenv("OLDPWD", current_directory, 1);
		setenv("PWD", getcwd(NULL, 0), 1);
		free(current_directory);
	}
	else
		perror("cd");
}
