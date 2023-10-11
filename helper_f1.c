#include "shell.h"

/**
 * _strcmp - Compare two strings lexicographically.
 *
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: An integer less than, equal to, or greater than zero if str1 is
 * found, respectively, to be less than, to match, or to be greater than str2.
 */
int _strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] && (str1[i] == str2[i]))
		i++;

	return (str1[i] - str2[i]);
}

/**
 * _strncmp - Compare a specified number of characters from two strings
 * lexicographically.
 *
 * @str1: The first string.
 * @str2: The second string.
 * @n: The maximum number of characters to compare.
 *
 * Return: An integer less than, equal to, or greater than zero if str1 is
 * found, respectively, to be less than, to match, or to be greater than str2.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i = 0;

	while (i < n && str1[i] && (str1[i] == str2[i]))
		i++;

	if (i == n)
		return (0);

	return (str1[i] - str2[i]);
}

/**
 * _strchr - Locate the first occurrence of a character in a string.
 *
 * @str: The string to be searched.
 * @character: The character to search for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 * or NULL if the character is not found.
 */
char *_strchr(const char *str, int character)
{
	while (*str != '\0')
	{
		if (*str == character)
			return ((char *)str);

		str++;
	}

	if (character == '\0')
		return ((char *)str);

	return (NULL);
}

/**
 * _strstr - Locate the first occurrence of a substring in a string.
 *
 * @haystack: The string to be searched.
 * @needle: The substring to search for.
 *
 * Return: A pointer to the first occurrence of the substring in the string,
 * or NULL if the substring is not found.
 */
char *_strstr(const char *haystack, const char *needle)
{
	size_t needle_len = _strlen(needle);

	while (*haystack)
	{
		if (_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);

		haystack++;
	}

	return (NULL);
}

/**
 * _strerror - Convert an error code into a human-readable error message.
 *
 * @errnum: the error code to be converted.
 *
 * Return: a pointer to the error message string.
 */
char *_strerror(int errnum)
{
	return (strerror(errnum));
}
