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
	(void)argv; /* without this part the system will flag a warning: unused parameter 'argv' bcuz we didn't use argv
	and this line of code says to the compiler that we intentionally are not using it */

	printf("%d\n", argc - 1);

	return (0);
}
