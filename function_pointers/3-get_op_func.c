#include "3-calc.h"
#include <stddef.h>
/**
 * get_op_func - selects the correct function for an operator
 * @s: operator passed to the program
 *
 * Return: pointer to the matching function, or NULL
 */
int (*get_op_func(char *s))(int, int)
{
	op_t ops[] = {
		{"+", op_add},
		{"-", op_sub},
		{"*", op_mul},
		{"/", op_div},
		{"%", op_mod}
	};
	int i;

	i = 0;
	while (i < 5)
	{
		if (s[0] == ops[i].op[0] && s[1] == '\0')
			return (ops[i].f);
		i++;
	}

	return (NULL);
}

