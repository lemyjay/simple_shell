#include "shell.h"

/**
 * _atoi - convert a string to an integer.
 *
 * @str: the string to convert.
 *
 * Return: the integer value, or 0 if conversion fails.
 */
int _atoi(char *str)
{
	int result = 0, sign = 1, i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;

	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}

		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (result * sign);
}
