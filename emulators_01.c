#include "shell.h"

/**
 * my_curr_dir - function that changes your current directory
 * @f: struct containing potential arguments
 *
 *  Return: always 0
 */
int my_curr_dir(struct_info *f)
{
	char *k, *to, buf[1024];
	int change_dir;

	k = getcwd(buf, 1024);
	if (!k)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!f->arg_vec[1])
	{
		to = get_environ(f, "HOME=");
		if (!to)
			change_dir =
				chdir((to = get_environ(f, "PWD=")) ? to : "/");
		else
			change_dir = chdir(to);
	}
	else if (str_cmp(f->arg_vec[1], "-") == 0)
	{
		if (!get_environ(f, "OLDPWD="))
		{
			puts(k);
			putchar('\n');
			return (1);
		}
		puts(get_environ(f, "OLDPWD=")), putchar('\n');
		change_dir = 
			chdir((to = get_environ(f, "OLDPWD=")) ? to : "/");
	}
	else
		change_dir = chdir(f->arg_vec[1]);
	if (change_dir == -1)
	{
		err_pr(f, "can't cd to ");
		puts_err(f->arg_vec[1]), putchar_err('\n');
	}
	else
	{
		set_environ(f, "OLDPWD", get_environ(f, "PWD="));
		set_environ(f, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * my_alias - function that applies same function as alias
 * @f: struct containing potential arguments
 *
 *  Return: always 0
 */
int my_alias(struct_info *f)
{
	int k = 0;
	char *s = NULL;
	struct_list *d = NULL;

	if (f->arg_count == 1)
	{
		d = f->alias;
		while (d)
		{
			alias_print(d);
			d = d->node;
		}
		return (0);
	}
	for (k = 1; f->arg_vec[k]; k++)
	{
		s = str_char(f->arg_vec[k], '=');
		if (s)
			alias_set(f, f->arg_vec[k]);
		else
			alias_print(node_begins(f->alias, f->arg_vec[k], '='));
	}

	return (0);
}

/**
 * my_history - function that gets my histoty list
 * @f: struct containing potential arguments
 *
 *  Return: always 0
 */
int my_history(struct_info *f)
{
	list_print(f->hist);
	return (0);
}

/**
 * my_help - function that displays help center
 * @f: struct containing potential arguments
 *
 *  Return: always 0
 */
int my_help(struct_info *f)
{
	char **gum;

	gum = f->arg_vec;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*gum);
	return (0);
}

/**
 * my_exit - function that exits the shell
 * @f: struct containing potential arguments
 *
 *  Return: always 0
 */
int my_exit(struct_info *f)
{
	int check_exit;

	if (f->arg_vec[1])
	{
		check_exit = err_a_to_i(f->arg_vec[1]);
		if (check_exit == -1)
		{
			f->stat = 2;
			err_pr(f, "Illegal number: ");
			puts_err(f->arg_vec[1]);
			putchar_err('\n');
			return (1);
		}
		f->num_err = err_a_to_i(f->arg_vec[1]);
		return (-2);
	}
	f->num_err = -1;
	return (-2);
}
