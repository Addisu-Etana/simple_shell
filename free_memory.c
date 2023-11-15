#include "shell.h"

/**
 * be_free - frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 *This function frees the memory pointed to by the pointer 'ptr' and sets it
 * to NULL to avoid any potential dangling pointers.
 * Return: 1 if the pointer was freed, 0 otherwise.
 */
int be_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
