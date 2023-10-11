#include "shell.h"

/**
 * _strcspn - Calculate the length of the initial segment of a string that
 * consists of characters not in a specified set.
 *
 * @str: The string to be searched.
 * @reject: A string containing the characters to be excluded.
 *
 * Return: The length of the initial segment of @str that contains characters
 * not present in @reject.
 */
size_t _strcspn(const char *str, const char *reject)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		if (_strchr(reject, str[length]) != NULL)
			break;

		length++;
	}

	return (length);
}

/**
 * _itoa - Convert an integer to a string.
 *
 * @num: The integer to convert.
 *
 * Return: A dynamically allocated string representing the integer.
 */
char *_itoa(int num)
{
	int i = 0, is_negative = 0, temp, index = 0, start = 0, end;
	char *str;

	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}
	temp = num;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	str = (char *)malloc((i + 1 + is_negative) * sizeof(char));
	(str == NULL) ? malloc_error() : (void)0;
	do {
		str[index++] = num % 10 + '0';
		num /= 10;
	} while (num > 0);
	if (is_negative)
		str[index++] = '-';
	str[index] = '\0';
	end = index - 1;
	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

/**
 * _memcpy - copy memory area
 *
 * @dest: pointer to the destination memory
 * @src: pointer to the source memory
 * @n: number of bytes to copy
 *
 * Return: pointer to the destination memory (dest)
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;
	size_t i;

	if (d == NULL && s == NULL)
		return (NULL);

	for (i = 0; i < n; i++)
		d[i] = s[i];

	return (dest);
}

/**
 * _realloc - Reallocate a memory block with a new size.
 *
 * @ptr: pointer to the previously allocated memory
 * @old_size: the size (in bytes) of the old allocated memory
 * @new_size: the new size (in bytes) to allocate
 *
 * Return: pointer to the newly allocated memory, or NULL on failure
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	size_t copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	copy_size = (old_size < new_size) ? old_size : new_size;
	_memcpy(new_ptr, ptr, copy_size);
	free(ptr);

	return (new_ptr);
}
