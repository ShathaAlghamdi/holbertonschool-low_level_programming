#include "variadic_functions.h"
#include <stdio.h>

/**
 * print_all - prints values according to a format string
 * @format: string containing argument type identifiers
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i;
	char *separator;
	char *str;

	i = 0;
	separator = "";

	va_start(args, format);

	while (format != NULL && format[i] != '\0')
	{
		if (format[i] == 'c')
		{
			printf("%s%c", separator, va_arg(args, int));
			separator = ", ";
		}
		if (format[i] == 'i')
		{
			printf("%s%d", separator, va_arg(args, int));
			separator = ", ";
		}
		if (format[i] == 'f')
		{
			printf("%s%f", separator, va_arg(args, double));
			separator = ", ";
		}
		if (format[i] == 's')
		{
			str = va_arg(args, char *);

			if (str == NULL)
				str = "(nil)";

			printf("%s%s", separator, str);
			separator = ", ";
		}

		i++;
	}

	va_end(args);
	printf("\n");
}
