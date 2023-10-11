#include "shell.h"

/**
 * parse_command - A function to parse the command into arguments.
 *
 * @command: the input command string to be parsed.
 * @args: an array to store the individual arguments.
 * @arg_count: a counter for the number of arguments found during parsing.
 */
void parse_command(char *command, char *args[], int *arg_count)
{
	char *token = strtok(command, " \t\n");

	while (token != NULL)
	{
		args[*arg_count] = token;
		(*arg_count)++;
		token = strtok(NULL, " \t\n");
	}

	args[*arg_count] = NULL;
}

/**
 * execute_child - A function to execute the command in the child process.
 *
 * @args: commands retreived after parsing the input from the terminal.
 */
void execute_child(char *args[])
{
	/*extern char **environ;*/

	/*execve(args[0], args, environ);*/

	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_parent - A function to handle the parent process (waiting for child).
 *
 * @pid: the pid of the parent.
 */
void handle_parent(pid_t pid)
{
	int status;
	char *str_exit = "Child process exited with status code: ";
	char *str_signal = "Child process terminated by signal: ";

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}

	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status), len = 0;

		len += write(STDOUT_FILENO, str_exit, _strlen(str_exit));
		len += write(STDOUT_FILENO, _itoa(exit_status), len);
		len += write(STDOUT_FILENO, "\n", 1);

		(len < 0) ? write_error() : (void)0;
		free(_itoa(exit_status));
	}
	else if (WIFSIGNALED(status))
	{
		int signal_number = WTERMSIG(status), len = 0;

		len += write(STDOUT_FILENO, str_signal, _strlen(str_signal));
		len += write(STDOUT_FILENO, _itoa(signal_number), len);
		len += write(STDOUT_FILENO, "\n", 1);

		(len < 0) ? write_error() : (void)0;
		free(_itoa(signal_number));
	}
}

/**
 * execute_command - Execute a command in a child process.
 *
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		free(command);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[MAX_INPUT_SIZE];
		int arg_count = 0;

		parse_command(command, args, &arg_count);
		execute_child(args);
	}
	else
	{
		handle_parent(pid);
	}
}
