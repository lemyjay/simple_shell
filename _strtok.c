#include "shell.h"

/**
 * token_len - Locates the delimiter index marking the end of the first token
 * contained within a string.
 *
 * @str: the string to be searched.
 * @delim: the delimiter character.
 *
 * Return: the delimiter index marking the end of the initial token pointed to
 * in str.
 */
int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - counts the number of delimited words contained within a
 * string.
 *
 * @str: the string to be searched.
 * @delim: the delimiter character.
 *
 * Return: the number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - tokenizes a string.
 *
 * @line: the string
 * @delim: the delimiter character to tokenize the string with
 *
 * Return: a pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, a, letters, b;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (a = 0; a < tokens; a++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[a] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[a])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (b = 0; b < letters; b++)
		{
			ptr[a][b] = line[index];
			index++;
		}
		ptr[a][b] = '\0';
	}
	ptr[a] = NULL;
	ptr[a + 1] = NULL;

	return (ptr);
}
