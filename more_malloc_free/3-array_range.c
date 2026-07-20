#include "main.h"
#include <stdlib.h>

/**
 * array_range - creates an array of integers
 * @min: minimum value
 * @max: maximum value
 *
 * Return: pointer to the new array, or NULL
 */
int *array_range(int min, int max)
{
	int *ptr;
	unsigned int size, i;

	if (min > max)
		return (NULL);

	size = max - min + 1;

	ptr = malloc(sizeof(int) * size);

	if (ptr == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		ptr[i] = min;
		min++;
	}

	return (ptr);
}
