#include "shell.h"

/**
 * gethistory_file -The function that gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *gethistory_file(info_t *info)
{
	char *buf, *dir;

	dir = value_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string_length(dir) +
				string_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * appends_history -The function that creates a file, or appends to
 *	an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int appends_history(info_t *info)
{
	ssize_t fd;
	char *filename = gethistory_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_xyz(node->str, fd);
		put_xyz('\n', fd);
	}
	put_xyz(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_file -The function that reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history_file(info_t *info)
{
	int x, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethistory_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			add_history_list(info, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		add_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_atindex(&(info->history), 0);
	re_number_history(info);
	return (info->histcount);
}

/**
 * add_history_list -The function that adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int add_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_toend(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * re_number_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int re_number_history(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
