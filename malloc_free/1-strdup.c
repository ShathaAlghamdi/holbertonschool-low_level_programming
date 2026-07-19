#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a duplicate of a string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL on failure
 */
char *_strdup(char *str)
{
	char *copy;
	int length;
	int i;

	if (str == NULL)
		return (NULL);

	length = 0;

	while (str[length] != '\0')
	{
		length++;
	}

	copy = malloc(sizeof(char) * (length + 1));

	if (copy == NULL)
		return (NULL);

	for (i = 0; i <= length; i++)
	{
		copy[i] = str[i];
	}

	return (copy);
}
