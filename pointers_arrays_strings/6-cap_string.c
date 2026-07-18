#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: string
 *
 * Return: pointer to str
 */
char *cap_string(char *str)
{
	int i, j;
	char sep[] = " \t\n,;.!?\"(){}";

	/* first character */
	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] -= 32;

	for (i = 0; str[i] != '\0'; i++)
	{
		for (j = 0; sep[j] != '\0'; j++)
		{
			if (str[i] == sep[j])
			{
				if (str[i + 1] >= 'a' &&
					str[i + 1] <= 'z')
				{
					str[i + 1] -= 32;
				}
			}
		}
	}

	return (str);
}
