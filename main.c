#include "shell.h"

/**
 * main - entry point
 * @arg_count: arg count
 * @arg_vec: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **arg_vec)
{
	struct_info f[] = { F_INIT };
	int file_dir = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_dir)
		: "r" (file_dir));

	if (arg_count == 2)
	{
		file_dir = open(arg_vec[1], O_RDONLY);
		if (file_dir == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_err(arg_vec[0]);
				puts_err(": 0: Can't open ");
				puts_err(arg_vec[1]);
				putchar_err('\n');
				putchar_err(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		f->read_fd = file_dir;
	}
	pop_environ_list(f);
	hist_read(f);
	hsh(f, arg_vec);
	return (EXIT_SUCCESS);
}
