#include "shell.h"

/**
 * print_prompt - Display a shell prompt.
 */
void print_prompt(void)
{
	char prompt[] = "$ ";
	ssize_t bytes_written = write(STDOUT_FILENO, prompt,
	sizeof(prompt) - 1);

	(bytes_written == -1) ? write_error() : (void)0;
}

/**
 * print_environment - A function to print current environment variables
 */
void print_environment(void)
{
	extern char **environ;
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
 * Return: 0 for success.
 */
int main(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t bytes_read;

	while (true)
	{
		print_prompt();
		fflush(stdout);

		bytes_read = _getline(&input, &input_size, stdin);

		if (bytes_read == -1)
		{
			free(input);
			break;
		}

		if (bytes_read == 0)
			break;

		input[bytes_read - 1] = '\0';

		if (_strcmp(input, "exit") == 0 || _strcmp(input, "quit") == 0)
			break;

		if (_strcmp(input, "env") == 0)
			print_environment();
		else
			execute_command(input);
	}

	free(input);

	return (0);
}
