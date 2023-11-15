#include "shell.h"

/**
 *input_string -The function that prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void input_string(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		wr_char_stderr(str[x]);
		x++;
	}
}

/**
 * wr_char_stderr -The function writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int wr_char_stderr(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * put_xyz -The function writes the character c to given f_d
 * @c: The character to print
 * @f_d: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_xyz(char c, int f_d)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(f_d, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * puts_xyz -The function that prints an input string
 * @str: the string to be printed
 * @f_d: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int puts_xyz(char *str, int f_d)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += put_xyz(*str++, f_d);
	}
	return (x);
}
