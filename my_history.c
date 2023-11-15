#include "shell.h"

/**
 * our_history -The function displays the history list, one command by line,
 *	preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int our_history(info_t *info)
{
	print_list_elements(info->history);
	return (0);
}

/**
 * un_set_alias -The function sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int un_set_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = string_locates(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_atindex(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - The function sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = string_locates(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (un_set_alias(info, str));

	un_set_alias(info, str);
	return (add_node_toend(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias -The function prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = string_locates(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * our_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int our_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = string_locates(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
