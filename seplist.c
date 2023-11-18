#include "shell.h"

/**
 * add_sep_node_end - adds separator at node end
 * @head: head of the linked list.
 * @seperate: separator found (; | &).
 * Return: address of the head.
 */
sept_list *add_sep_node_end(sept_list **head, char seperate)
{
	sept_list *new, *temp;

	new = malloc(sizeof(sept_list));
	if (new == NULL)
		return (NULL);

	new->seperator = seperate;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sept_list - frees a seperator list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sept_list(sept_list **head)
{
	sept_list *temp;
	sept_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds line at end of node
 * @head: head of the linked list.
 * @line: line to be added
 * Return: address of the head.
 */
l_list *add_line_node_end(l_list **head, char *line)
{
	l_list *new, *temp;

	new = malloc(sizeof(l_list));
	if (new == NULL)
		return (NULL);

	new->next = NULL;
	new->line = line;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_l_list - free entry point
 * @head: head of the linked list.
 * Return: no return.
 */
void free_l_list(l_list **head)
{
	l_list *temp;
	l_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
