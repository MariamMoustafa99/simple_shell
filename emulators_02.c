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
 * alias_rep - function that replaces an alias
 * @f: struct containing potential arguments
 *
 * Return: 1 if alias is replaced or 0 otherwise
 */
int alias_rep(struct_info *f)
{
	int k;
	struct_list *d;
	char *m;

	for (k = 0; k < 10; k++)
	{
		d = node_starts_with(f->alias, f->argv[0], '=');
		if (!d)
			return (0);
		free(f->argv[0]);
		m = _strchr(d->str, '=');
		if (!m)
			return (0);
		m = _strdup(m + 1);
		if (!m)
			return (0);
		f->argv[0] = m;
	}
	return (1);
}

/**
 * alias_set - function that sets an alias to string
 * @f: struct containing potential arguments
 * @t: string alias
 *
 * Return: 1 on failure or 0 on success
 */
int alias_set(struct_info *f, char *t)
{
	char *x;

	x = _strchr(t, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (alias_unset(f, t));

	alias_unset(f, t);
	return (add_node_end(&(f->alias), t, 0) == NULL);
}

/**
 * alias_unset - function that unsets an alias to string
 * @f: struct containing potential arguments
 * @t: string alias
 *
 * Return: 1 on failure or 0 on success
 */
int alias_unset(struct_info *f, char *t)
{
	char *x, z;
	int val;

	x = _strchr(t, '=');
	if (!x)
		return (1);
	z = *x;
	*x = 0;
	val = delete_node_at_index(&(f->alias),
		get_node_index(f->alias, node_starts_with(f->alias, t, -1)));
	*x = z;
	return (val);
}
