#include "shell.h"

/**
 * de_limiter - function that checks if a character is a delimeter
 * @character: the char to check
 * @m: delimeter
 *
 * Return: 1 if delimeter or 0 if not
 */
int de_limiter(char character, char *m)
{
	while (*m)
		if (*m++ == character)
			return (1);
	return (0);
}

/**
 * is_alpha - function that checks if char is an alphabetic character
 * @s: The character to input
 *
 * Return: 1 if s is an alphabetic char or 0 otherwise
 */
int is_alpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * a_to_i - function that converts a string to an integer
 * @str: the string to be converted
 *
 * Return: integer or 0 if no  numbers in str
 */
int a_to_i(char *str)
{
	int k, sign = 1, g = 0, m;
	unsigned int val = 0;

	for (k = 0;  str[k] != '\0' && g != 2; k++)
	{
		if (str[k] == '-')
			sign *= -1;

		if (str[k] >= '0' && str[k] <= '9')
		{
			g = 1;
			val *= 10;
			val += (str[k] - '0');
		}
		else if (g == 1)
			g = 2;
	}

	if (sign == -1)
		m = -val;
	else
		m = val;

	return (m);
}

/**
 * err_a_to_i - function that converts a string to an integer
 * @str: the string to be converted
 *
 * Return: integer or 0 if no  numbers in str
 */
int err_a_to_i(char *str)
{
	int k = 0;
	unsigned long int val = 0;

	if (*str == '+')
		str++;
	for (k = 0;  str[k] != '\0'; k++)
	{
		if (str[k] >= '0' && str[k] <= '9')
		{
			val *= 10;
			val += (str[k] - '0');
			if (val > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (val);
}
