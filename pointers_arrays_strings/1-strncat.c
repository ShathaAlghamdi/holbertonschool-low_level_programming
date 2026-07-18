#include "main.h"

/**
 * _strncat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * @n: maximum number of bytes from src
 *
 * Return: pointer to dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	/* Find the end of dest */
	while (dest[i] != '\0')
	{
		i++;
	}

	/* Copy at most n characters from src */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	/* Add null terminator */
	dest[i] = '\0';

	return (dest);
}
