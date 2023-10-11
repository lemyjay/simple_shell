#include "shell.h"

/**
 * init_buffer - Initialize the buffer and lineptr.
 *
 * @lineptr: A buffer to store the input line.
 * @n: The size of lineptr.
 */
static void init_buffer(char **lineptr, size_t *n)
{
	*n = READ_SIZE;
	*lineptr = malloc(*n);
	if (*lineptr == NULL)
		malloc_error();
}

/**
 * process_buffer - Process the input buffer
 *
 * @lineptr: A pointer to the buffer where the line is stored
 * @n: A pointer to the size of the buffer
 * @buffer: The input buffer to process
 * @buffer_index: A pointer to the current index in the buffer
 * @bytes_read: The number of bytes read into the buffer
 * @newline_found: A flag indicating if a newline character was found
 *
 * Return: The total number of bytes processed.
 */
ssize_t process_buffer(char **lineptr, size_t *n, char *buffer,
ssize_t *buffer_index, ssize_t bytes_read, int *newline_found)
{
	ssize_t total_bytes = 0;

	while (*buffer_index < bytes_read)
	{
		if (total_bytes >= READ_SIZE - 1)
		{
			char *temp = _realloc(*lineptr, *n, (*n) * 2);

			if (temp == NULL)
				return (-1);

			*lineptr = temp;
		}

		(*lineptr)[total_bytes++] = buffer[(*buffer_index)++];

		if ((*lineptr)[total_bytes - 1] == '\n')
		{
			*newline_found = 1;
			break;
		}
	}

	return (total_bytes);
}

/**
 * _getline - Read a line from a file stream
 *
 * @lineptr: A pointer to the buffer storing the line
 * @n: A pointer to the size of the buffer
 * @stream: The input stream to read from
 *
 * Return: The number of bytes read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[READ_SIZE];
	static ssize_t buffer_index;
	ssize_t bytes_read = 0, total_bytes = 0;
	int newline_found = 0;

	buffer_index = 0;
	if (!lineptr || !n || !stream)
		return (-1);

	(*lineptr == NULL || *n == 0) ? init_buffer(lineptr, n) : (void)0;

	while (1)
	{
		if (buffer_index == 0)
		{
			bytes_read = read(fileno(stream), buffer, READ_SIZE);

			if (bytes_read <= 0)
				return ((total_bytes == 0) ? -1 : total_bytes);
		}

		total_bytes = process_buffer(lineptr, n, buffer,
		&buffer_index, bytes_read, &newline_found);

		if (newline_found)
		{
			(*lineptr)[total_bytes] = '\0';
			return (total_bytes);
		}
		buffer_index = 0;
	}
}
