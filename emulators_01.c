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
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!f->argv[1])
	{
		to = _getenv(f, "HOME=");
		if (!to)
			change_dir =
				chdir((to = _getenv(f, "PWD=")) ? to : "/");
		else
			change_dir = chdir(to);
	}
	else if (_strcmp(f->argv[1], "-") == 0)
	{
		if (!_getenv(f, "OLDPWD="))
		{
			_puts(k);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(f, "OLDPWD=")), _putchar('\n');
		change_dir =
			chdir((to = _getenv(f, "OLDPWD=")) ? to : "/");
	}
	else
		change_dir = chdir(f->argv[1]);
	if (change_dir == -1)
	{
		print_error(f, "can't cd to ");
		_eputs(f->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(f, "OLDPWD", _getenv(f, "PWD="));
		_setenv(f, "PWD", getcwd(buf, 1024));
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

	if (f->argc == 1)
	{
		d = f->alias;
		while (d)
		{
			print_alias(d);
			d = d->next;
		}
		return (0);
	}
	for (k = 1; f->argv[k]; k++)
	{
		s = _strchr(f->argv[k], '=');
		if (s)
			set_alias(f, f->argv[k]);
		else
			print_alias(node_starts_with(f->alias, f->argv[k], '='));
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
	print_list(f->history);
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

	gum = f->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*gum);
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

	if (f->argv[1])
	{
		check_exit = _erratoi(f->argv[1]);
		if (check_exit == -1)
		{
			f->status = 2;
			print_error(f, "Illegal number: ");
			_eputs(f->argv[1]);
			_eputchar('\n');
			return (1);
		}
		f->err_num = _erratoi(f->argv[1]);
		return (-2);
	}
	f->err_num = -1;
	return (-2);
}
