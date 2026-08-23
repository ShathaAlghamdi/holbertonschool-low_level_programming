#include "main.h"

/**
 * string_length - returns the length of a string
 * @s: string
 *
 * Return: length of string
 */
int string_length(char *s)
{
	if (*s == '\0')
		return (0);

	return (1 + string_length(s + 1));
}

/**
 * check_palindrome - checks characters from both ends
 * @s: string
 * @start: starting index
 * @end: ending index
 *
 * Return: 1 if palindrome, otherwise 0
 */
int check_palindrome(char *s, int start, int end)
{
	if (start >= end)
		return (1);

	if (s[start] != s[end])
		return (0);

	return (check_palindrome(s, start + 1, end - 1));
}

/**
 * is_palindrome - checks if a string is a palindrome
 * @s: string
 *
 * Return: 1 if palindrome, otherwise 0
 */
int is_palindrome(char *s)
{
	int len;

	len = string_length(s);

	return (check_palindrome(s, 0, len - 1));
}
