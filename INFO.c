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

	f->file_name = arg_vec[0];
	if (f->arg)
	{
		f->arg_vec = str_to_word(f->arg, " \t");
		if (!f->arg_vec)
		{

			f->arg_vec = malloc(sizeof(char *) * 2);
			if (f->arg_vec)
			{
				f->arg_vec[0] = str_dup(f->arg);
				f->arg_vec[1] = NULL;
			}
		}
		for (k = 0; f->arg_vec && f->arg_vec[k]; k++)
			;
		f->arg_count = k;

		alias_rep(f);
		var_rep(f);
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
	free_str(f->arg_vec);
	f->arg_vec = NULL;
	f->str_path = NULL;
	if (free_all)
	{
		if (!f->cmd_buffer)
			free(f->arg);
		if (f->en_viron)
			list_free(&(f->en_viron));
		if (f->hist)
			list_free(&(f->hist));
		if (f->alias)
			list_free(&(f->alias));
		free_str(f->environ);
			f->environ = NULL;
		free_pointer((void **)f->cmd_buffer);
		if (f->read_fd > 2)
			close(f->read_fd);
		putchar(BUFFER_FLUSH);
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
	f->arg_vec = NULL;
	f->str_path = NULL;
	f->arg_count = 0;
}
