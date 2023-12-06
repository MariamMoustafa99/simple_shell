#include "shell.h"

/**
 * *str_char - function that searches for location of a char in a string
 * @word: string to search in
 * @x: char to search for
 *
 * Return: pointer to loacation of char
 */
char *str_char(char *word, char x)
{
	do {
		if (*word == x)
			return (word);
	} while (*word++ != '\0');

	return (NULL);
}

/**
 * char_duplicate - function that duplicates chars
 * @str_path: path string
 * @r: the starting index
 * @p: the stopping index
 *
 * Return: pointer to the new buffer
 */
char *char_duplicate(char *str_path, int r, int p)
{
	static char buffer[1024];
	int m = 0, j = 0;

	for (j = 0, m = r; m < p; m++)
		if (str_path[m] != ':')
			buffer[j++] = str_path[m];
	buffer[j] = 0;
	return (buffer);
}

/**
 * *str_num_copy - function that copies a num of chars from a string
 * @out: output string
 * @in: string to copy from
 * @i: num of chars to copy
 *
 * Return: copied string
 */
char *str_num_copy(char *out, char *in, int i)
{
	int x, m;
	char *ret = out;

	x = 0;
	while (in[x] != '\0' && x < 1 - 1)
	{
		out[x] = in[x];
		x++;
	}
	if (x < i)
	{
		m = x;
		while (m < i)
		{
			out[m] = '\0';
			m++;
		}
	}
	return (ret);
}

/**
 * *str_num_concat - function that concatenates 2 strings with max num of bytes
 * @out: string 1
 * @in: string 2
 * @i: num of bytes
 *
 * Return: the concatenated string
 */
char *str_num_concat(char *out, char *in, int i)
{
	int k, z;
	char *ret = out;

	k = 0;
	z = 0;
	while (out[k] != '\0')
		k++;
	while (in[z] != '\0' && z < i)
	{
		out[k] = in[z];
		k++;
		z++;
	}
	if (z < i)
		out[k] = '\0';
	return (ret);
}
