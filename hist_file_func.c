#include "shell.h"

/**
 * hist_read - function that reads history from a file
 * @f: struct containing potential arguments
 *
 * Return: history count if success or 0 otherwise
 */
int hist_read(struct_info *f)
{
	int k, end = 0, count_ln = 0;
	ssize_t file, read_len, file_size = 0;
	struct stat st;
	char *buffer = NULL, *file_name = hist_get(f);

	if (!file_name)
		return (0);

	file = open(file_name, O_RDONLY);
	free(file_name);
	if (file == -1)
		return (0);
	if (!fstat(file, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_len = read(file, buffer, file_size);
	buffer[file_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(file);
	for (k = 0; k < file_size; k++)
		if (buffer[k] == '\n')
		{
			buffer[k] = 0;
			hist_add_list(f, buffer + end, count_ln++);
			end = k + 1;
		}
	if (end != k)
		hist_add_list(f, buffer + end, count_ln++);
	free(buffer);
	f->hist_count = count_ln;
	while (f->hist_count-- >= HIST_MAX)
		node_del_index(&(f->hist), 0);
	hist_renum(f);
	return (f->hist_count);
}

/**
 * hist_get - function that gets the history file
 * @f: struct containing potential arguments
 *
 * Return: history file
 */

char *hist_get(struct_info *f)
{
	char *buffer, *tory;

	tory = get_environ(f, "HOME=");
	if (!tory)
		return (NULL);
	buffer = malloc(sizeof(char) * (str_len(tory) + str_len(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	str_copy(buffer, tory);
	str_concat(buffer, "/");
	str_concat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * hist_write - function that creates a file, or appends to an existing file
 * @f: struct containing potential arguments
 *
 * Return: 1 on success or -1 otherwise
 */
int hist_write(struct_info *f)
{
	ssize_t file_dir;
	char *f_name = hist_get(f);
	struct_list *d = NULL;

	if (!f_name)
		return (-1);

	file_dir = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (file_dir == -1)
		return (-1);
	for (d = f->hist; d; d = d->node)
	{
		puts_filedes(d->c, file_dir);
		put_filedes('\n', file_dir);
	}
	put_filedes(BUFFER_FLUSH, file_dir);
	close(file_dir);
	return (1);
}

/**
 * hist_renum - function that renumbers the history linked list after changes
 * @f: struct containing potential arguments
 *
 * Return: the new history count
 */
int hist_renum(struct_info *f)
{
	struct_list *d = f->hist;
	int k = 0;

	while (d)
	{
		d->x = k++;
		d = d->node;
	}
	return (f->hist_count = k);
}


/**
 * hist_add_list - function that adds entry to a history linked list
 * @f: struct containing potential arguments
 * @buffer: buffer
 * @count_ln: history linecount
 *
 * Return: Always 0
 */
int hist_add_list(struct_info *f, char *buffer, int count_ln)
{
	struct_list *d = NULL;

	if (f->hist)
		d = f->hist;
	node_add_end(&d, buffer, count_ln);

	if (!f->hist)
		f->hist = d;
	return (0);
}
