#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * get_table - returns the crackme character table
 *
 * Return: pointer to the character table
 */
char *get_table(void)
{
	static char table[] = {
		'A', '-', 'C', 'H', 'R', 'D', 'w', '8',
		'7', 'l', 'N', 'S', '0', 'E', '9', 'B',
		'2', 'T', 'i', 'b', 'g', 'p', 'n', 'M',
		'V', 'y', 's', '5', 'X', 'z', 'v', 't',
		'O', 'G', 'J', 'c', 'Y', 'L', 'U', '+',
		'4', 'm', 'j', 'W', '6', 'f', 'x', 'q',
		'Z', 'e', 'F', '3', 'Q', 'a', '1', 'r',
		'P', 'h', 'd', 'K', 'I', 'o', 'u', 'k'
	};

	return (table);
}

/**
 * key_sum - calculates the sum-based key index
 * @name: username
 * @length: username length
 *
 * Return: key index
 */
unsigned int key_sum(char *name, unsigned int length)
{
	unsigned int sum = 0, i;

	for (i = 0; i < length; i++)
		sum += (unsigned char)name[i];
	return ((sum ^ 79u) & 63u);
}

/**
 * key_product - calculates the product-based key index
 * @name: username
 * @length: username length
 *
 * Return: key index
 */
unsigned int key_product(char *name, unsigned int length)
{
	unsigned int product = 1, i;

	for (i = 0; i < length; i++)
		product *= (unsigned char)name[i];
	return ((product ^ 85u) & 63u);
}

/**
 * key_max - calculates the maximum-character key index
 * @name: username
 * @length: username length
 *
 * Return: key index
 */
unsigned int key_max(char *name, unsigned int length)
{
	unsigned int maximum = (unsigned char)name[0], i;

	for (i = 0; i < length; i++)
		if ((unsigned char)name[i] > maximum)
			maximum = (unsigned char)name[i];
	srand(maximum ^ 14u);
	return ((unsigned int)rand() & 63u);
}

/**
 * key_squares - calculates the square-sum key index
 * @name: username
 * @length: username length
 *
 * Return: key index
 */
unsigned int key_squares(char *name, unsigned int length)
{
	unsigned int squares = 0, value, i;

	for (i = 0; i < length; i++)
	{
		value = (unsigned char)name[i];
		squares += value * value;
	}
	return ((squares ^ 239u) & 63u);
}

/**
 * key_random - calculates the final pseudo-random key index
 * @name: username
 *
 * Return: key index
 */
unsigned int key_random(char *name)
{
	unsigned int value = 0, i;

	for (i = 0; i < (unsigned char)name[0]; i++)
		value = (unsigned int)rand();
	return ((value ^ 229u) & 63u);
}

/**
 * main - generates a valid key for crackme5
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments
 *
 * Return: 0 on success, 1 if no username is supplied
 */
int main(int argc, char **argv)
{
	char *table = get_table();
	char *name;
	unsigned int length;

	if (argc != 2)
		return (1);
	name = argv[1];
	length = (unsigned int)strlen(name);
	printf("%c", table[(length ^ 59u) & 63u]);
	printf("%c", table[key_sum(name, length)]);
	printf("%c", table[key_product(name, length)]);
	printf("%c", table[key_max(name, length)]);
	printf("%c", table[key_squares(name, length)]);
	printf("%c", table[key_random(name)]);
	return (0);
}
