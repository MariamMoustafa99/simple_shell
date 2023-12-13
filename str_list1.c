#include "shell.h"

/**
 * list_print - function that prints all elements of struct_list linked list
 * @d: a pointer to 1st node
 *
 * Return: size of the list
 */
size_t list_print(const struct_list *d)
{
	size_t k = 0;

	while (d)
	{
		puts(num_conv(d->x, 10, 0));
		putchar(':');
		putchar(' ');
		puts(d->c ? d->c : "(nil)");
		puts("\n");
		d = d->node;
		k++;
	}
	return (k);
}

/**
 * str_list_print - function that prints only str elements 
 * of struct_list linked list
 * @d: a pointer to 1st node
 *
 * Return: size of the list
 */
size_t str_list_print(const struct_list *d)
{
	size_t k = 0;

	while (d)
	{
		puts(d->c ? d->c : "(nil)");
		puts("\n");
		d = d->node;
		k++;
	}
	return (k);
}

/**
 * list_length - function that determines the length of struct_list linked list
 * @d: a pointer to 1st node
 *
 * Return: size of the list
 */
size_t list_length(const struct_list *d)
{
	size_t k = 0;

	while (d)
	{
		d = d->node;
		k++;
	}
	return (k);
}

/**
 * str_list_arr - function that returns an array of strings of the struct_list
 * @h: a pointer to 1st node
 *
 * Return: array of strings
 */
char **str_list_arr(struct_list *h)
{
	struct_list *d = h;
	size_t k = list_length(h), m;
	char **arr_strs;
	char *r;

	if (!h || !k)
		return (NULL);
	arr_strs = malloc(sizeof(char *) * (k + 1));
	if (!arr_strs)
		return (NULL);
	for (k = 0; d; d = d->node, k++)
	{
		r = malloc(str_len(d->c) + 1);
		if (!r)
		{
			for (m = 0; m < k; m++)
				free(arr_strs[m]);
			free(arr_strs);
			return (NULL);
		}

		r = str_copy(r, d->c);
		arr_strs[k] = r;
	}
	arr_strs[k] = NULL;
	return (arr_strs);
}

/**
 * list_free - function that frees all nodes of a list
 * @ptr_h: address of pointer to 1st node
 *
 * Return: void
 */
void list_free(struct_list **ptr_h)
{
	struct_list *d, *d_next, *h;

	if (!ptr_h || !*ptr_h)
		return;
	h = *ptr_h;
	d = h;
	while (d)
	{
		d_next = d->node;
		free(d->c);
		free(d);
		d = d_next;
	}
	*ptr_h = NULL;
}
