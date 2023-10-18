#ifndef SHELL_H
#define SHELL_H

/* Custom header files included */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_SIZE 1024
#define READ_SIZE 1024
extern char **environ;

/* Declaration of prototypes of helper functions */
size_t _strlen(const char *str);
char *_strdup(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strncpy(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(const char *str1, const char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strchr(const char *str, int character);
char *_strstr(const char *haystack, const char *needle);
char *_strerror(int errnum);
size_t _strcspn(const char *str, const char *reject);
char *_itoa(int num);
int _atoi(char *str);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char **_strtok(char *line, char *delim);
char *_strtoken(char *str, const char *delim);

/* Declaration of prototypes of functions for the project */
void interactive_mode(void);
void non_interactive_mode(char *command);
void print_environment(void);
void find_command(char *args[], char *input);
void print_prompt(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void parse_command(char *command, char *args[], int *arg_count);
void handle_exit_command(char **args, int arg_count, char *input);
void setenv_command(char *args[]);
void unsetenv_command(char *args[]);
void handle_cd_command(char *args[]);


/* Error handling functions */
void write_error(void);
void malloc_error(void);

#endif /* SHELL_H */
