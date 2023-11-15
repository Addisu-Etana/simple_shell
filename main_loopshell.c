#include "shell.h"

/**
 * main_shell_loop -The function tells about main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info_struct(info);
		if (interactive_mode(info))
			_puts("$ ");
		wr_char_stderr(BUF_FLUSH);
		r = get_input_newline(info);
		if (r != -1)
		{
			set_info_struct(info, av);
			builtin_ret = find_builtin_command(info);
			if (builtin_ret == -1)
				find_cmd_path(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		free_info_struct(info, 0);
	}
	appends_history(info);
	free_info_struct(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin_command -The function that finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", our_exit},
		{"env", new_setenv},
		{"help", pwd_help},
		{"history", our_history},
		{"setenv", new_setenv},
		{"unsetenv", our_unset_env},
		{"cd", our_cd},
		{"alias", our_alias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (string_comparison(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[x].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd_path -The function finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd_path(info_t *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!our_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(info, value_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd_run(info);
	}
	else
	{
		if ((interactive_mode(info) || value_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && our_cmd(info, info->argv[0]))
			fork_cmd_run(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error_msg(info, "not found\n");
		}
	}
}

/**
 * fork_cmd_run -The function that forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd_run(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_return_enviro(info)) == -1)
		{
			free_info_struct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error_msg(info, "Permission denied\n");
		}
	}
}
