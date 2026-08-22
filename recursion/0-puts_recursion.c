#include <stdio.h>
#include <stdlib.h>
/** * _puts_recursion - prints a string followed by a new line
 * @s: string to print
 * Return: nothing
 */
void _puts_recursion(char *s)
{
    /* إذا وصلنا لنهاية string */
    if (*s == '\0')
    {
        _putchar('\n');
        return;
    }

    /* اطبع الحرف الحالي */
    _putchar(*s);

    /* روح للحرف التالي : my recursion part  */
    _puts_recursion(s + 1);
}