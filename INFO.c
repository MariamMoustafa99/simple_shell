#include "shell.h"

/**
 * info_set - function that initializes struct_info
 * @f: struct containing potential arguments
 * @arg_vec: argument vector
 *
 * Return: void
 */
void info_set(struct_info *f, char **arg_vec)
{
	int k = 0;

	f->fname = arg_vec[0];
	if (f->arg)
	{
		f->argv = strtow(f->arg, " \t");
		if (!f->argv)
		{

			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _strdup(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (k = 0; f->argv && f->argv[k]; k++)
			;
		f->argc = k;

		replace_alias(f);
		replace_vars(f);
	}
}

/**
 * info_free - function that frees struct_info
 * @f: struct containing potential arguments
 * @free_all: True in case all fields are freed
 *
 * Return: void
 */
void info_free(struct_info *f, int free_all)
{
	ffree(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (free_all)
	{
		if (!f->cmd_buf)
			free(f->arg);
		if (f->env)
			free_list(&(f->env));
		if (f->history)
			free_list(&(f->history));
		if (f->alias)
			free_list(&(f->alias));
		ffree(f->environ);
			f->environ = NULL;
		bfree((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * info_clear - function that clears struct_info
 * @f: struct containing potential arguments
 *
 * Return: void
 */
void info_clear(struct_info *f)
{
	f->arg = NULL;
	f->argv = NULL;
	f->path = NULL;
	f->argc = 0;
}
