#include <stdlib.h>
#include <string.h>
#include "lists.h"

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: address of the pointer to the first node
 * @str: string to duplicate into the new node
 *
 * Return: address of the new node, or NULL on failure
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new_node;
	unsigned int length = 0;

	if (head == NULL || str == NULL)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->str = strdup(str);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}

	while (str[length] != '\0')
		length++;

	new_node->len = length;
	new_node->next = *head;
	*head = new_node;

	return (new_node);
}
