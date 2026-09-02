#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - generates a valid key for crackme5
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments
 *
 * Return: 0 on success, 1 if no username is supplied
 */
int main(int argc, char **argv)
{
	char table[] = "A-CHRDw87lNS0E9B2TibgpnMVys5XzvtOGJcYLU+"
		"4mjW6fxqZeF3Qa1rPhdKIouk";
	char *username;
	unsigned int length, sum, product, maximum, squares, random_value;
	unsigned int i;

	if (argc != 2)
		return (1);

	username = argv[1];
	length = (unsigned int)strlen(username);
	printf("%c", table[(length ^ 59u) & 63u]);

	sum = 0;
	product = 1;
	maximum = (unsigned char)username[0];
	squares = 0;
	for (i = 0; i < length; i++)
	{
		unsigned int value = (unsigned char)username[i];

		sum += value;
		product *= value;
		if (value > maximum)
			maximum = value;
		squares += value * value;
	}

	printf("%c", table[(sum ^ 79u) & 63u]);
	printf("%c", table[(product ^ 85u) & 63u]);

	srand(maximum ^ 14u);
	printf("%c", table[(unsigned int)rand() & 63u]);

	printf("%c", table[(squares ^ 239u) & 63u]);

	random_value = 0;
	for (i = 0; i < (unsigned char)username[0]; i++)
		random_value = (unsigned int)rand();
	printf("%c", table[(random_value ^ 229u) & 63u]);

	return (0);
}

