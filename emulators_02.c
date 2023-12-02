#include "shell.h"

/**
 * alias_print - function that prints alias string
 * @d: node for the alias
 *
 * Return: 1 on failure or 0 on success
 */
int alias_print(struct_list *d)
{
	char *v = NULL, *b = NULL;

	if (f)
	{
		v = _strchr(d->str, '=');
		for (b = d->str; b <= v; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(v + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_set - function that sets an alias to string
 * @d: struct containing potential arguments
 * @t: string alias
 *
 * Return: 1 on failure or 0 on success
 */
int alias_set(struct_info *d, char *t)
{
	char *x;

	x = _strchr(t, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (alias_unset(d, t));

	alias_unset(d, t);
	return (add_node_end(&(d->alias), t, 0) == NULL);
}

/**
 * alias_unset - function that unsets an alias to string
 * @d: struct containing potential arguments
 * @t: string alias
 *
 * Return: 1 on failure or 0 on success
 */
int alias_unset(struct_info *d, char *t)
{
	char *x, z;
	int val;

	x = _strchr(t, '=');
	if (!x)
		return (1);
	z = *x;
	*x = 0;
	val = delete_node_at_index(&(d->alias),
		get_node_index(d->alias, node_starts_with(d->alias, t, -1)));
	*x = z;
	return (val);
}
