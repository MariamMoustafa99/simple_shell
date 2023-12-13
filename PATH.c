#include "shell.h"

/**
 * cmd_exec - function that determines if a file is an executable cmd
 * @f: struct containing potential arguments
 * @th: path to the file
 *
 * Return: 1 if true or 0 otherwise
 */
int cmd_exec(struct_info *f, char *th)
{
	struct status state;

	(void)f;
	if (!th || status(th, &state))
		return (0);

	if (state.state_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * path_finder - function that finds the cmd in the PATH string
 * @f: struct containing potential arguments
 * @str_path: path str
 * @commmand: the command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *path_finder(struct_info *f, char *str_path, char *commmand)
{
	int k = 0, position = 0;
	char *th;

	if (!str_path)
		return (NULL);
	if ((str_len(command) > 2) && start_with(command, "./"))
	{
		if (cmd_exec(f, command))
			return (command);
	}
	while (1)
	{
		if (!str_path[k] || str_path[k] == ':')
		{
			th = char_duplicate(str_path, position, k);
			if (!*th)
				str_concat(th, command);
			else
			{
				str_concat(th, "/");
				str_concat(th, command);
			}
			if (cmd_exec(f, th))
				return (th);
			if (!str_path[k])
				break;
			position = k;
		}
		k++;
	}
	return (NULL);
}
