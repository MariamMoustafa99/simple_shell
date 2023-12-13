
#include "shell.h"

/**
 * comments_rem - function that replaces first appearance of '#' with '\0'
 * @str: address of the string to modify
 *
 * Return: Always 0;
 */
void comments_rem(char *str)
{
	int k;

	for (k = 0; str[k] != '\0'; k++)
		if (str[k] == '#' && (!k || str[k - 1] == ' '))
		{
			str[k] = '\0';
			break;
		}
}

/**
 * inter_active - function that returns true if shell is in interactive mode
 * @f: struct containing potential arguments
 *
 * Return: 1 if in interactive mode or 0 otherwise
 */
int inter_active(struct_info *f)
{
	return (isatty(STDIN_FILENO) && f->read_fd <= 2);
}

/**
 * num_conv - function that converts integer to a character
 * @n: number
 * @s: base
 * @g: argument flags
 *
 * Return: charcter
 */
char *num_conv(long int n, int s, int g)
{
	static char *ray;
	static char buffer[50];
	char m_sign = 0;
	char *t;
	unsigned long x = n;

	if (!(g & CONV_UNSIGNED) && n < 0)
	{
		x = -n;
		m_sign = '-';

	}
	ray = g & CONV_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	t = &buffer[49];
	*t = '\0';

	do	{
		*--t = ray[x % s];
		x /= s;
	} while (x != 0);

	if (m_sign)
		*--t = m_sign;
	return (t);
}

/**
 * err_pr - function that prints an error message
 * @f: struct containing potential arguments
 * @err_str: string containing specified error type
 *
 * Return: 0 if no numbers in str or converted number or otherwise
 *        -1 on error
 */
void err_pr(struct_info *f, char *err_str)
{
	puts_err(f->file_name);
	puts_err(": ");
	dec_pr(f->line_count, STDERR_FILENO);
	puts_err(": ");
	puts_err(f->arg_vec[0]);
	puts_err(": ");
	puts_err(err_str);
}

/**
 * dec_pr - function that prints a decimal (integer) number in (base 10)
 * @p: the input number
 * @file_des: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int dec_pr(int p, int file_des)
{
	int (*__putchar)(char) = put_char;
	int k, n = 0;
	unsigned int absolute, rent;

	if (file_des == STDERR_FILENO)
		__putchar = putchar_err;
	if (p < 0)
	{
		absolute = -p;
		__putchar('-');
		n++;
	}
	else
		absolute = p;
	rent = absolute;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (absolute / k)
		{
			__putchar('0' + rent / k);
			n++;
		}
		rent %= k;
	}
	__putchar('0' + rent);
	n++;

	return (n);
}
