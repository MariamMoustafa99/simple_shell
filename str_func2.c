#include "shell.h"

/**
 * puts - function that prints your input string
 * @m: string to be printed
 *
 * Return: void
 */
void puts(char *m)
{
	int k = 0;

	if (!m)
		return;
	while (m[i] != '\0')
	{
		put_char(m[k]);
		k++;
	}
}

/**
 * put_char - function that prints a character
 * @s: char to be printed
 *
 * Return: 1 on success, -1 on failure
 */
int put_char(char s)
{
	static int f;
	static char buffer[WRITE_BUFFER_SIZE];

	if (s == BUFFER_FLUSH || f >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, f);
		f = 0;
	}
	if (s != BUFFER_FLUSH)
		buf[f++] = s;
	return (1);
}

/**
 * str_copy - function that copies a string
 * @s1: output string
 * @s2: string to be copied
 *
 * Return: a pointer to output string
 */
char *str_copy(char *s1, char *s2)
{
	int j = 0;

	if (s1 == s2 || s2 == 0)
		return (s1);
	while (s2[j])
	{
		s1[j] = s2[j];
		j++;
	}
	s1[j] = 0;
	return (s1);
}

/**
 * str_dup - function that duplicates a string
 * @x: string
 *
 * Return: pointer to the duplicated string
 */
char *str_dup(const char *x)
{
	int l = 0;
	char *val;

	if (x == NULL)
		return (NULL);
	while (*x++)
		l++;
	val = malloc(sizeof(char) * (l + 1));
	if (!val)
		return (NULL);
	for (l++; l--;)
		val[l] = *--x;
	return (val);
}
