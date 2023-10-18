#include "shell.h"

/**
 * print_prompt - Display a shell prompt.
 */
void print_prompt(void)
{
	if (write(STDOUT_FILENO, "($) ", 4) == -1)
		write_error();
}

/**
 * print_environment - A function to print current environment variables
 */
void print_environment(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * main - Entry point to the shell program
 *
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 * Return: 0 for success.
 */
int main(int argc, char *argv[])
{
	if (argc == 1)
		interactive_mode();
	else if (argc == 2)
	{
		char *command = argv[0];

		non_interactive_mode(command);
	}
	else
	{
		fprintf(stderr, "Usage: %s [command]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return (0);
}
