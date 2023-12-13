#include "shell.h"

/**
 * hsh - main shell loop
 * @f: struct containing potential arguments
 * @arg_vec: the argument vector
 *
 * Return: 0 on success or 1 on failure
 */
int hsh(info_t *f, char **arg_vec)
{
	ssize_t m = 0;
	int ret = 0;

	while (m != -1 && ret != -2)
	{
		info_clear(f);
		if (inter_active(f))
			puts("$ ");
		putchar_err(BUFFER_FLUSH);
		m = get_line_bef(f);
		if (m != -1)
		{
			info_set(f, arg_vec);
			ret = cmd_builtin(f);
			if (ret == -1)
				cmd_find(f);
		}
		else if (inter_active(f))
			putchar('\n');
		info_free(f, 0);
	}
	hist_write(f);
	info_free(f, 1);
	if (!inter_active(f) && f->stat)
		exit(f->stat);
	if (ret == -2)
	{
		if (f->num_err == -1)
			exit(f->stat);
		exit(f->num_err);
	}
	return (ret);
}

/**
 * cmd_builtin - function that finds a builtin command
 * @f: struct containing potential arguments
 *
 * Return: -2 if exit() or -1 if not found or 0 on success
 */
int cmd_builtin(struct_info *f)
{
	int k, ret = -1;
	built_in_table builtintable[] = {
		{"exit", my_exit},
		{"env", my_environ},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_set_environ},
		{"unsetenv", my_unset_environ},
		{"cd", my_curr_dir},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (k = 0; builtintable[k].flag; k++)
		if (str_cmp(f->argv[0], builtintable[k].flag) == 0)
		{
			f->line_count++;
			ret = builtintable[k].func(f);
			break;
		}
	return (ret);
}

/**
 * cmd_fork - function that forks an exececution thread to run a command
 * @f: struct containing potential arguments
 *
 * Return: void
 */
void cmd_fork(struct_info *f)
{
	pid_t pid_ch;

	pid_ch = fork();
	if (pid_ch == -1)
	{
		perror("Error:");
		return;
	}
	if (pid_ch == 0)
	{
		if (execve(f->str_path, f->arg_vec, get_environ(f)) == -1)
		{
			info_free(f, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(f->stat));
		if (WIFEXITED(f->stat))
		{
			f->stat = WEXITSTATUS(f->stat);
			if (f->stat == 126)
				print_error(f, "Permission denied\n");
		}
	}
}

/**
 * cmd_find - function that finds a command in PATH
 * @f: struct containing potential arguments
 *
 * Return: void
 */
void cmd_find(struct_info *f)
{
	char *r = NULL;
	int m, n;

	f->str_path = f->arg_vec[0];
	if (f->lc_flag == 1)
	{
		f->line_count++;
		f->lc_flag = 0;
	}
	for (m = 0, n = 0; f->arg[m]; k++)
		if (!de_limiter(f->arg[m], " \t\n"))
			n++;
	if (!n)
		return;

	r = path_finder(f, get_environ(f, "PATH="), f->arg_vec[0]);
	if (r)
	{
		f->str_path = r;
		cmd_fork(f);
	}
	else
	{
		if ((inter_active(f) || get_environ(f, "PATH=")
			|| f->arg_vec[0][0] == '/') && cmd_exec(f, f->arg_vec[0]))
			cmd_fork(f);
		else if (*(f->arg) != '\n')
		{
			f->stat = 127;
			print_error(f, "not found\n");
		}
	}
}
