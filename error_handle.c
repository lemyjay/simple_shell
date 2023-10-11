#include "shell.h"

/**
 * write_error - Handles write function failure
 */
void write_error(void)
{
	perror("write");
	exit(EXIT_FAILURE);
}

/**
 * malloc_error - Handles malloc function failure
 */
void malloc_error(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}
