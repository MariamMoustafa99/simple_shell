
#include "shell.h"

/**
 * signal_handler - function that blocks ctrl-C command
 * @n_sig: the signal number
 *
 * Return: void
 */
void signal_handler(__attribute__((unused))int n_sig)
{
	puts("\n");
	puts("$ ");
	putchar(BUF_FLUSH);
}

/**
 * buffer_read - function that reads a buffer
 * @f: struct containing potential arguments
 * @buffer: buffer
 * @k: size
 *
 * Return: buffer size
 */
ssize_t buffer_read(struct_info *f, char *buffer, size_t *k)
{
	ssize_t m = 0;

	if (*k)
		return (0);
	m = read(f->read_fd, buffer, READ_BUFFER_SIZE);
	if (m >= 0)
		*k = m;
	return (m);
}

/**
 * buffer_input - function that adds a buffer
 * @f: struct containing potential arguments
 * @buffer: address of buffer
 * @rem: address of remaining variable
 *
 * Return: bytes added
 */
ssize_t buffer_input(struct_info *f, char **buffer, size_t *rem)
{
	ssize_t m = 0;
	size_t x = 0;

	if (!*rem)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal_handler);
#if USE_GETLINE
		m = getline(buffer, &x, stdin);
#else
		m = get_line_next(f, buffer, &x);
#endif
		if (m > 0)
		{
			if ((*buffer)[m - 1] == '\n')
			{
				(*buffer)[m - 1] = '\0';
				m--;
			}
			f->lc_flag = 1;
			comments_rem(*buffer);
			hist_add_list(f, *buffer, f->hist_count++);
			if (str_char(*buffer, ';'))
			{
				*rem = m;
				f->cmd_buffer = buffer;
			}
		}
	}
	return (m);
}

/**
 * get_line_bef - function that gets a line before the newline
 * @f: struct containing potential arguments
 *
 * Return: length of buffer
 */
ssize_t get_line_bef(struct_info *f)
{
	static char *buffer;
	static size_t k, l, length;
	ssize_t m = 0;
	char **place_buf = &(f->arg), *c;

	putchar(BUFFER_FLUSH);
	m = buffer_input(f, &buffer, &length);
	if (m == -1)
		return (-1);
	if (length)
	{
		l = k;
		c = buffer + k;

		chain_checked(f, buffer, &l, k, length);
		while (l < length)
		{
			if (chain_del(f, buffer, &l))
				break;
			l++;
		}

		k = l + 1;
		if (k >= length)
		{
			k = length = 0;
			f->cmd_buffer_type = CMD_NORM;
		}

		*place_buf = c;
		return (str_len(c));
	}

	*place_buf = buffer;
	return (m);
}

/**
 * get_line_next - function that gets the next line of input from STDIN
 * @f: struct containing potential arguments
 * @pointer: address of pointer to buffer that is preallocated or NULL
 * @s: size of preallocated pointer buffer if not NULL
 *
 * Return: length of buffer
 */
int get_line_next(struct_info *f, char **pointer, size_t *s)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t k, length;
	size_t n;
	ssize_t m = 0, d = 0;
	char *c = NULL, *ptr_new = NULL, *x;

	c = *pointer;
	if (c && s)
		d = *s;
	if (k == length)
		k = length = 0;

	m = buffer_read(f, buffer, &length);
	if (m == -1 || (m == 0 && length == 0))
		return (-1);

	x = str_char(buffer + k, '\n');
	n = x ? 1 + (unsigned int)(x - buffer) : length;
	ptr_new = re_allocate(c, d, d ? d + n : n + 1);
	if (!ptr_new)
		return (c ? free(c), -1 : -1);

	if (d)
		_strncat(ptr_new, buffer + k, n - k);
	else
		_strncpy(ptr_new, buffer + k, n - k + 1);

	d += n - k;
	k = n;
	c = ptr_new;

	if (s)
		*s = d;
	*pointer = c;
	return (d);
}
