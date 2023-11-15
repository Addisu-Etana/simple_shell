#include "shell.h"

/**
 * our_env -The function that prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: eachtime 0
 */
int our_env(info_t *info)
{
	print_str_list(info->env);
	return (0);
}

/**
 * value_getenv -The function gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *value_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with_address(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * new_setenv -The function initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int new_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		input_string("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * our_unset_env -The function remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: eachtime 0
 */
int our_unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		input_string("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		remove_env_variable(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_toend(&node, environ[i], 0);
	info->env = node;
	return (0);
}
