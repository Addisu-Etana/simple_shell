#include "shell.h"

/**
 * our_cmd - Determines if a file is an executable command
 *
 * @info: The info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int our_cmd(info_t *info, char *path)
{
	struct stat start;

	(void)info;
	if (!path || stat(path, &start))
		return (0);

	if (start.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - Duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[y++] = pathstr[x];
	buf[y] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH of the string
 * @info: The info struct
 * @pathstr: The PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, current_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_length(cmd) > 2) && starts_with_address(cmd, "./"))
	{
		if (our_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = duplicate_chars(pathstr, current_position, x);
			if (!*path)
				strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (our_cmd(info, path))
				return (path);
			if (!pathstr[x])
				break;
			current_position = x;
		}
		x++;
	}
	return (NULL);
}
