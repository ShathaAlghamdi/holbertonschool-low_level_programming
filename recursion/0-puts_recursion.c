#include "main.h"

/**
 * _puts_recursion - Prints a string followed by a new line
 * @s: String to print
 *
 * Return: Nothing
 */
void _puts_recursion(char *s)
{
	/* إذا وصلنا لنهاية الـ string */
	if (*s == '\0')
	{
		_putchar('\n');
		return;
	}

	/* اطبع الحرف الحالي */
	_putchar(*s);

	/* My recursion part: روح للحرف التالي */
	_puts_recursion(s + 1);
}
