#include "main.h"

/**
 * _strlen_recursion - Returns the length of a string
 * @s: String to count
 *
 * Return: Length of the string
 */
int _strlen_recursion(char *s)
{
	/* Base case: وصلنا لنهاية الـ string */
	if (*s == '\0')
	{
		return (0);
	}

	/* Count this character + count the rest */
	return (1 + _strlen_recursion(s + 1));
}