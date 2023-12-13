#include "shell.h"

/**
 * pop_environ_list - function that populates an environment linked list
 * @f: struct containing potential arguments
 *
 * Return: always 0
 */
int pop_environ_list(struct_info *f)
{
	struct_list *d = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		node_add_end(&d, environ[k], 0);
	f->en_viron = d;
	return (0);
}

/**
 * copy_environ - function that returns str array copy of our environment
 * @f: struct containing potential arguments
 *
 * Return: always 0
 */
char **copy_environ(struct_info *f)
{
	if (!f->environ || f->env_change)
	{
		f->environ = str_list_arr(f->en_viron);
		f->env_change = 0;
	}

	return (f->environ);
}

/**
 * set_environ - function that initializes a new env var
 * @f: struct containing potential arguments
 * @r: str environment var
 * @u: str environment var value
 *
 * Return: always 0
 */
int set_environ(struct_info *f, char *r, char *u)
{
	char *buffer = NULL;
	struct_list *d;
	char *c;

	if (!r || !u)
		return (0);

	buffer = malloc(str_len(r) + str_len(u) + 2);
	if (!buffer)
		return (1);
	str_copy(buffer, r);
	str_concat(buffer, "=");
	str_concat(buffer, u);
	d = f->en_viron;
	while (d)
	{
		c = start_with(d->c, r);
		if (c && *c == '=')
		{
			free(d->c);
			d->c = buffer;
			f->env_change = 1;
			return (0);
		}
		d = d->node;
	}
	node_add_end(&(f->en_viron), buffer, 0);
	free(buffer);
	f->env_change = 1;
	return (0);
}

/**
 * unset_environ - function that removes an environment var
 * @f: struct containing potential arguments
 * @r: str environment var
 *
 *  Return: 1 if deleted or 0 otherwise
 */
int unset_environ(struct_info *f, char *r)
{
	struct_list *d = f->en_viron;
	size_t k = 0;
	char *c;

	if (!d || !f)
		return (0);

	while (d)
	{
		c = start_with(d->c, r);
		if (c && *c == '=')
		{
			f->env_change = node_del_index(&(f->en_viron), k);
			k = 0;
			d = f->en_viron;
			continue;
		}
		d = d->node;
		k++;
	}
	return (f->env_change);
}
