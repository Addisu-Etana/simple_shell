#include "shell.h"

/**
 * clear_info_struct -The function initializes info_t struct
 * @info: struct address
 */
void clear_info_struct(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info_struct -The function initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info_struct(info_t *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_string_words(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;

		replace_alias_string(info);
		replace_vars_string(info);
	}
}

/**
 * free_info_struct -The function frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info_struct(info_t *info, int all)
{
	free_string(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_all_list(&(info->env));
		if (info->history)
			free_all_list(&(info->history));
		if (info->alias)
			free_all_list(&(info->alias));
		free_string(info->environ);
			info->environ = NULL;
		be_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
