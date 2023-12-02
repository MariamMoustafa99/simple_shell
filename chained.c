#include "shell.h"

/**
 * var_rep - function that replaces variables in a string
 * @f: struct containing potential arguments
 *
 * Return: 1 if var is replaced or 0 otherwise
 */
int var_rep(struct_info *f)
{
	int k = 0;
	struct_list *d;

	for (k = 0; f->argv[k]; k++)
	{
		if (f->argv[k][0] != '$' || !f->argv[k][1])
			continue;

		if (!_strcmp(f->argv[k], "$?"))
		{
			str_rep(&(f->argv[k]),
				_strdup(convert_number(f->status, 10, 0)));
			continue;
		}
		if (!_strcmp(f->argv[k], "$$"))
		{
			str_rep(&(f->argv[k]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		d = node_starts_with(f->env, &f->argv[k][1], '=');
		if (d)
		{
			str_rep(&(f->argv[k]),
				_strdup(_strchr(d->str, '=') + 1));
			continue;
		}
		str_rep(&f->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * str_rep - function that replaces a string
 * @str_old: address to the old str
 * @str_new: address to the new str
 *
 * Return: 1 if replaced, 0 otherwise
 */
int str_rep(char **str_old, char *str_new)
{
	free(*str_old);
	*str_old = str_new;
	return (1);
}

/**
 * chain_del - function that checks if the current char in buffer
 *      is a chain delimeter
 * @f: struct containing potential arguments
 * @buffer: char buffer
 * @c: address of the current pos in buffer
 *
 * Return: 1 if a chain delimeter or 0 otherwise
 */
int chain_del(struct_info *f, char *buffer, size_t *c)
{
	size_t i = *c;

	if (buffer[j] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		f->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		f->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		f->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*c = i;
	return (1);
}

/**
 * chain_checked - function that checks whether to continue
 *     chaining based on prev status
 * @f: struct containing potential arguments
 * @buffer: char buffer
 * @c: address of the current pos in buffer
 * @k: starting pos in buffer
 * @n: the length of buffer
 *
 * Return: void
 */
void chain_checked(struct_info *f, char *buffer, size_t *c, size_t k, size_t n)
{
	size_t i = *c;

	if (f->cmd_buf_type == CMD_AND)
	{
		if (f->status)
		{
			buffer[k] = 0;
			j = n;
		}
	}
	if (f->cmd_buf_type == CMD_OR)
	{
		if (!f->status)
		{
			buf[k] = 0;
			i = n;
		}
	}

	*c = i;
}
