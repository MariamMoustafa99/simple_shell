#include "shell.h"

/**
 * **str_to_word - function that split string to words
 * @m: string input
 * @del: delimiter string
 *
 * Return: a pointer to an array of strings or NULL on error
 */

char **str_to_word(char *m, char *del)
{
	int a, b, c, d, numOfWords = 0;
	char **str;

	if (m == NULL || m[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; m[i] != '\0'; a++)
		if (!de_limiter(m[a], del) && (de_limiter(m[a + 1], del) || !m[a + 1]))
			numOfWords++;

	if (numOfWords == 0)
		return (NULL);
	str = malloc((1 + numOfWords) * sizeof(char *));
	if (!str)
		return (NULL);
	for (a = 0, b = 0; b < numOfWords; b++)
	{
		while (de_limiter(m[a], del))
			a++;
		c = 0;
		while (!de_limiter(m[a + c], del) && m[a + c])
			c++;
		str[b] = malloc((c + 1) * sizeof(char));
		if (!str[b])
		{
			for (c = 0; c < b; c++)
				free(str[c]);
			free(str);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			str[b][d] = m[a++];
		str[b][d] = 0;
	}
	str[b] = NULL;
	return (str);
}

/**
 * **str_to_word2 - function that split string to words
 * @m: string input
 * @del: delimiter string
 *
 * Return: a pointer to an array of strings or NULL on error
 */
char **str_to_word2(char *m, char del)
{
	int a, b, c, d, numofWords = 0;
	char **str;

	if (m == NULL || m[0] == 0)
		return (NULL);
	for (a = 0; m[a] != '\0'; a++)
		if ((m[a] != del && m[a + 1] == del) ||
		    (m[a] != del && !m[a + 1]) || m[a + 1] == del)
			numofWords++;
	if (numofWords == 0)
		return (NULL);
	str = malloc((1 + numofWords) * sizeof(char *));
	if (!str)
		return (NULL);
	for (a = 0, b = 0; b < numofWords; b++)
	{
		while (m[a] == del && m[a] != del)
			a++;
		c = 0;
		while (m[a + c] != del && m[a + c] && m[a + c] != del)
			c++;
		str[b] = malloc((c + 1) * sizeof(char));
		if (!str[b])
		{
			for (c = 0; c < b; c++)
				free(str[c]);
			free(str);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			str[b][d] = m[i++];
		str[b][d] = 0;
	}
	str[b] = NULL;
	return (str);
}
