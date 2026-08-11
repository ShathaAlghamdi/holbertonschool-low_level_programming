#include <stdio.h>

/**
 * main - prints the number of arguments passed
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	(void)argv; /* This line is used to avoid unused variable warning */
	printf("%d\n", argc - 1);

	return (0);
}
