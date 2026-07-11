#include "main.h"

/**
 * print_triangle - prints a triangle
 * @size: size of the triangle
 *
 * Return: void
 */
void print_triangle(int size)
{
	int row, col, spaces, hashes;

	if (size <= 0)
	{
		_putchar('\n');
		return;
	}

	for (row = 1; row <= size; row++)
	{
		spaces = size - row;
		hashes = row;

		for (col = 0; col < spaces; col++)
		{
			_putchar(' ');
		}

		for (col = 0; col < hashes; col++)
		{
			_putchar('#');
		}

		_putchar('\n');
	}
}
