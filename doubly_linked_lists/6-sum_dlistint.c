#include "lists.h"

/**
 * sum_dlistint - returns the sum of all the data in a dlistint_t list
 * @head: pointer to the head of the list
 *
 * Return: sum of all nodes
 */
int sum_dlistint(dlistint_t *head)
{
	int sum = 0;

	while (head != NULL)
	{
		sum += head->n;
		head = head->next;
	}

	return (sum);
}
