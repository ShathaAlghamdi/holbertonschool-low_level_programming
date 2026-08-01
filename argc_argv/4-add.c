#include <stdio.h>
#include <stdlib.h>

/**
 * main - adds positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	int i, j, sum;

	sum = 0;

	for (i = 1; i < argc; i++)
	{
		for (j = 0; argv[i][j] != '\0'; j++)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (1);
			}
		}
		sum += atoi(argv[i]); /*atoi() stands for ASCII to Integer.

It is a function from the C standard library (stdlib.h) that converts a string into an integer.
the manuel way ...... 
	sum = 0;

	for (i = 1; i < argc; i++)
	{
		number = 0;

		for (j = 0; argv[i][j] != '\0'; j++)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error\n");
				return (1);
			}

			number = number * 10 + (argv[i][j] - '0');
		}

		sum += number;
	}*/
	}

	printf("%d\n", sum);

	return (0);
}
