#include "shell.h"

/**
 * free_pointer - function that nulls the address and free a pointer
 * @ad: the address of the pointer to be freed
 *
 * Return: 1 on success or 0 otherwise
 */

int free_pointer(void **ad)
{
	if (ad && *ad)
	{
		free(*ad);
		*ad = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_str - ffunction that frees a string
 * @str: string
 *
 * Return: none
 */
void free_str(char **str)
{
	char **x = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(x);
}

/**
 * *memory_set - function that fills the memory with a constant byte
 * @p: pointer to the memory area
 * @k: byte to fill the memory with
 * @x: number of bytes to be filled
 *
 * Return: a pointer to the filled memory area
 */
char *memory_set(char *p, char k, unsigned int x)
{
	unsigned int m;

	for (m = 0; m < x; x++)
		p[m] = k;
	return (p);
}

/**
 * re_allocate - function that reallocates a block of memory
 * @ref: a pointer to the previous allocated block
 * @size1: old byte size of block
 * @size2: new byte size of block
 *
 * Return: a pointer to new memory block
 */
void *re_allocate(void *ref, unsigned int size1, unsigned int size2)
{
	char *m;

	if (!ref)
		return (malloc(size2));
	if (!size2)
		return (free(ref), NULL);
	if (size2 == size1)
		return (ref);

	m = malloc(size2);
	if (!m)
		return (NULL);

	size1 = size1 < size2 ? size1 : size2;
	while (size1--)
		m[size1] = ((char *)ref)[size1];
	free(ref);
	return (m);
}
