#include "shell.h"

/**
 * node_begins - function that returns node whose str begins with a prefix
 * @h: a pointer to 1st node
 * @x: string to match
 * @r: next char after prefix
 *
 * Return: node if matched or NULL
 */
struct_list *node_begins(struct_list *h, char *x, char r)
{
	char *c = NULL;

	while (h)
	{
		c = start_with(h->c, x);
		if (c && ((r == -1) || (*c == r)))
			return (h);
		h = h->node;
	}
	return (NULL);
}

/**
 * node_get_index - function that gets the index of the node
 * @h: a pointer to 1st node
 * @d: pointer to the node
 *
 * Return: index of node or -1 if error
 */
ssize_t node_get_index(struct_list *h, struct_list *d)
{
	size_t k = 0;

	while (h)
	{
		if (h == d)
			return (k);
		h = h->node;
		k++;
	}
	return (-1);
}

/**
 * node_add_start - function that adds a node at the start of a list
 * @h: address of pointer to 1st node
 * @d_str: string field of node
 * @d_index: index of node used by history
 *
 * Return: size of the list
 */
struct_list *node_add_start(struct_list **h, const char *d_str, int d_index)
{
	struct_list *h_new;

	if (!h)
		return (NULL);
	h_new = malloc(sizeof(struct_list));
	if (!h_new)
		return (NULL);
	memory_set((void *)h_new, 0, sizeof(struct_list));
	h_new->x = d_index;
	if (d_str)
	{
		h_new->c = str_dup(d_str);
		if (!h_new->c)
		{
			free(h_new);
			return (NULL);
		}
	}
	h_new->node = *h;
	*h = h_new;
	return (h_new);
}

/**
 * node_add_end - function that adds a node at the end of a list
 * @h: address of pointer to 1st node
 * @d_str: string field of node
 * @d_index: index of node used by history
 *
 * Return: size of the list
 */
struct_list *node_add_end(struct_list **h, const char *d_str, int d_index)
{
	struct_list *d_new, *d;

	if (!h)
		return (NULL);

	d = *h;
	d_new = malloc(sizeof(struct_list));
	if (!d_new)
		return (NULL);
	memory_set((void *)d_new, 0, sizeof(struct_list));
	d_new->x = d_index;
	if (d_str)
	{
		d_new->c = str_dup(d_str);
		if (!d_new->c)
		{
			free(d_new);
			return (NULL);
		}
	}
	if (d)
	{
		while (d->node)
			d = d->node;
		d->node = d_new;
	}
	else
		*h = d_new;
	return (d_new);
}

/**
 * node_del_index - function that deletes a node at a given index
 * @h: address of pointer to 1st node
 * @x: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int node_del_index(struct_list **h, unsigned int x)
{
	struct_list *d, *d_prev;
	unsigned int k = 0;

	if (!h || !*h)
		return (0);

	if (!x)
	{
		d = *h;
		*h = (*h)->node;
		free(d->c);
		free(d);
		return (1);
	}
	d = *h;
	while (d)
	{
		if (k == x)
		{
			d_prev->node = d->node;
			free(d->c);
			free(d);
			return (1);
		}
		k++;
		d_prev = d;
		d = d->node;
	}
	return (0);
}
