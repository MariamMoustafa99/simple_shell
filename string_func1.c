#include "shell.h"

/**
 * start_with - checks if str2 starts with str1
 * @str1: string to search for in str2
 * @str2: string to search in
 *
 * Return: the address of next character_ of str1 or NULL
 */
char *start_with(const char *str1, const char *str2)
{
	while (*str2)
		if (*str2++ != *str1++)
			return (NULL);
	return ((char *)str1);
}

/**
 * str_len - function that returns length of a string
 * @str: string
 *
 * Return: length of the string
 */
int str_len(char *str)
{
	int k = 0;

	if (!str)
		return (0);

	while (*str++)
		k++;
	return (k);
}

/**
 * str_concat - fumction that concatenates 2 strings
 * @str1: string 1
 * @str2: string 2
 *
 * Return: pointer to concatenated string
 */
char *str_concat(char *str1, char *str2)
{
	char *concat = str1;

	while (*str1)
		str1++;
	while (*str2)
		*str1++ = *str2++;
	*str1 = *str2;
	return (concat);
}

/**
 * str_comp - function that compares two strings
 * @str1: string 1
 * @str2: tstring 2
 *
 * Return: -1 if str1 less than str2, 1 if str1 larger than str2
 * or 0 if str1 == str2
 */
int str_comp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
