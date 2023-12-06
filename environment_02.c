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
		add_node_end(&d, environ[k], 0);
	f->env = d;
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
	if (!f->environ || f->env_changed)
	{
		f->environ = list_to_strings(f->env);
		f->env_changed = 0;
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

	buffer = malloc(_strlen(r) + _strlen(u) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, r);
	_strcat(buffer, "=");
	_strcat(buffer, u);
	d = f->env;
	while (d)
	{
		c = starts_with(d->str, r);
		if (c && *c == '=')
		{
			free(d->str);
			d->str = buffer;
			f->env_changed = 1;
			return (0);
		}
		d = d->next;
	}
	add_node_end(&(f->env), buffer, 0);
	free(buffer);
	f->env_changed = 1;
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
	struct_list *d = f->env;
	size_t k = 0;
	char *c;

	if (!d || !f)
		return (0);

	while (d)
	{
		c = starts_with(d->str, r);
		if (c && *c == '=')
		{
			f->env_changed = delete_node_at_index(&(f->env), k);
			k = 0;
			d = f->env;
			continue;
		}
		d = d->next;
		k++;
	}
	return (f->env_changed);
}
