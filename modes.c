#include "shell.h"

/**
 * interactive_mode - Run the shell in interactive mode.
 */
void interactive_mode(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t bytes_read;

	while (1)
	{
		char *args[MAX_INPUT_SIZE];
		int arg_count = 0;

		print_prompt();
		fflush(stdout);
		bytes_read = _getline(&input, &input_size, stdin);

		if (bytes_read == -1)
		{
			write(1, "\n", 1);
			break;
		}
		if (bytes_read == 0)
			break;

		input[bytes_read - 1] = '\0';
		parse_command(input, args, &arg_count);
		if (_strcmp(args[0], "quit") == 0 && arg_count == 1)
			break;
		if (_strcmp(args[0], "exit") == 0)
			handle_exit_command(args, arg_count, input);
		if (_strcmp(args[0], "env") == 0 && arg_count == 1)
			print_environment();
		else if (_strcmp(args[0], "setenv") == 0)
			setenv_command(args);
		else if (_strcmp(args[0], "unsetenv") == 0)
			unsetenv_command(args);
		else if (_strcmp(args[0], "cd") == 0)
			handle_cd_command(args);
		else
			find_command(args, input);
	}
	free(input);
}

/**
 * non_interactive_mode - Run the shell in non-interactive mode with a given
 * command.
 *
 * @command: The command to execute.
 */
void non_interactive_mode(char *command)
{
	char *args[MAX_INPUT_SIZE];
	int arg_count = 0;
	char *input = _strdup(command);

	if (input == NULL)
	{
		perror("strdup");
		return;
	}

	parse_command(input, args, &arg_count);
	if (_strcmp(args[0], "exit") == 0)
		handle_exit_command(args, arg_count, input);
	if (_strcmp(args[0], "env") == 0 && arg_count == 1)
		print_environment();
	else if (_strcmp(args[0], "setenv") == 0)
		setenv_command(args);
	else if (_strcmp(args[0], "unsetenv") == 0)
		unsetenv_command(args);
	else if (_strcmp(args[0], "cd") == 0)
		handle_cd_command(args);
	else
		find_command(args, input);
	write(1, "\n", 1);
	free(input);
}


