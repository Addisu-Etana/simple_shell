#include "shell.h"

/**
 * interactive_mode - The function checks if the shell is in interactive mode.
 * @info: Pointer to the info structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * our_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int our_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalphabetic - The function checks for an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
 */
int _isalphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * string_integer_convert - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer, or 0 if no numbers in the string.
 */
int string_integer_convert(char *s)
{
	int x, sign = 1, flag = 0, output;

	unsigned int result = 0;

	for (x = 0; s[x] != '\0' && flag != 2; x++)
	{
		if (s[x] == '-')
			sign *= -1;
		if (s[x] >= '0' && s[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

