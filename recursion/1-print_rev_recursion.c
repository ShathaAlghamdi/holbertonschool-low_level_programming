#include "main.h"

/**
 * _print_rev_recursion - Prints a string in reverse
 * @s: String to print
 *
 * Return: Nothing
 */
void _print_rev_recursion(char *s)
{
	/* إذا وصلنا لنهاية الـ string وقف */
	if (*s == '\0')
		return;

	/* My recursion part: روح للحرف التالي */
	_print_rev_recursion(s + 1);

	/* اطبع الحرف الحالي أثناء الرجوع */
	_putchar(*s);
}