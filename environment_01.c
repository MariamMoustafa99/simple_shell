#include "shell.h"

/**
 * my_environ - function that prints my current environment
 * @f: struct containing potential arguments
 *
 * Return: always 0
 */
int my_environ(struct_info *f)
{
	print_list_str(f->env);
	return (0);
}

/**
 * my_set_environ - function that initializes a new env var
 * @f: struct containing potential arguments
 *
 * Return: always 0
 */
int my_set_environ(struct_info *f)
{
	if (f->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_environ(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_environ - function that removes an environment var
 * @f: struct containing potential arguments
 *
 * Return: always 0
 */
int my_unset_environ(struct_info *f)
{
	int k;

	if (f->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= f->argc; k++)
		unset_environ(f, f->argv[k]);

	return (0);
}

/**
 * get_environ - function that gets the value of an environment var
 * @f: struct containing potential arguments
 * @env_name: name of environment var
 *
 * Return: value of the environment var
 */
char *get_environ(struct_info *f, const char *env_name)
{
	struct_list *d = f->env;
	char *c;

	while (d)
	{
		c = starts_with(d->str, env_name);
		if (c && *c)
			return (c);
		d = d->next;
	}
	return (NULL);
}
