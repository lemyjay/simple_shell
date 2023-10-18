#include "shell.h"

/**
 * handle_exit_command - Handle the "exit" command with arguments.
 *
 * @args: array of command arguments.
 * @arg_count: number of arguments.
 * @input: the input string.
 */
void handle_exit_command(char **args, int arg_count, char *input)
{
	if (arg_count > 1)
	{
		int exit_status = atoi(args[1]);

		free(input);
		if (exit_status != 0)
			exit(exit_status);
		else
		{
			perror("exit");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		free(input);
		exit(EXIT_SUCCESS);
	}
}

/**
 * execute_command - Execute a command using execve
 *
 * @args: an array of arguments for the command.
 * @input: the input to free in case of an error.
 * @command: the command to execute.
 */
void execute_command(char *command, char *args[], char *input)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		free(input);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			free(input);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}

/**
 * find_command - search for a command in the PATH and execute it
 *
 * @args: an array of arguments containing the command as the first element
 * @input: the input string to free in case of an error
 */
void find_command(char *args[], char *input)
{
	char *command = args[0];

	if (_strchr(command, '/') != NULL)
		execute_command(command, args, input);
	else
	{
		char *path = getenv("PATH"), *path_copy, *path_token;
		int command_found = 0;

		path_copy = _strdup(path);
		if (path_copy == NULL)
		{
			perror("strdup");
			free(input);
			exit(EXIT_FAILURE);
		}
		path_token = _strtoken(path_copy, ":");
		while (path_token != NULL)
		{
			char command_path[MAX_INPUT_SIZE];

			_strcpy(command_path, path_token);
			_strcat(command_path, "/");
			_strcat(command_path, command);
			if (access(command_path, X_OK) == 0)
			{
				execute_command(command_path, args, input);
				command_found = 1;
				break;
			}
			path_token = _strtoken(NULL, ":");
		}
		free(path_copy);
		if (!command_found)
			fprintf(stderr, "%s: command not found\n", command);
	}
}
