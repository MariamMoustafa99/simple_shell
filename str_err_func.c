#include "shell.h"

/**
 * put_filedes - function that writes a char to a file descriptor
 * @p: char to write
 * @file_des: filedescriptor to write to
 *
 * Return: 1 on success or -1 on error
 */
int put_filedes(char p, int file_des)
{
	static int k;
	static char buffer[WRITE_BUFFER_SIZE];

	if (p == BUFFER_FLUSH || k >= WRITE_BUFFER_SIZE)
	{
		write(file_des, buffer, k);
		k = 0;
	}
	if (p != BUFFER_FLUSH)
		buffer[k++] = p;
	return (1);
}

/**
 * puts_filedes - function that writes an input str to a file descriptor
 * @p: char to write
 * @file_des: filedescriptor to write to
 *
 * Return: num of chars written
 */
int puts_filedes(char *p, int file_des)
{
	int k = 0;

	if (!p)
		return (0);
	while (*p)
	{
		k += put_filedes(*p++, file_des);
	}
	return (k);
}

/**
 * puts_err - function that prints an input string to stderr
 * @c: string
 *
 * Return: void
 */
void puts_err(char *c)
{
	int k = 0;

	if (!c)
		return;
	while (c[k] != '\0')
	{
		putchar_err(c[k]);
		k++;
	}
}

/**
 * putchar_err - function that prints a char to stderr
 * @p: char
 *
 * Return: 1 on success or -1 on error
 */
int putchar_err(char p)
{
	static int k;
	static char buffer[WRITE_BUFFER_SIZE];

	if (p == BUFFER_FLUSH || k >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, k);
		k = 0;
	}
	if (p != BUFFER_FLUSH)
		buffer[k++] = p;
	return (1);
}
