/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/22/06 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2017/22/06 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						sortedInsert(t_files** head, t_files* new_node)
{
	t_files				*current;

	if (*head == NULL || ft_strcmp((*head)->name, new_node->name) > 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *head;
		while (current->next != NULL
				&& ft_strcmp(current->next->name, new_node->name) < 0)
		{
				current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void						sortedInsertTime(t_files** head, t_files* new_node)
{
	t_files				*current;

	if (*head == NULL || (*head)->mtime - new_node->mtime < 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL
				&& current->next->mtime - new_node->mtime > 0)
			current = current->next;
		if (current->next != NULL && current->next->mtime - new_node->mtime == 0)
		{
			if (ft_strcmp(current->next->name, new_node->name) > 0)
			{
				new_node->next = current->next;
				current->next = new_node;
			}
			else
			{
				while (current->next != NULL
						&& ft_strcmp(current->next->name, new_node->name) < 0
						&& current->next->mtime - new_node->mtime == 0)
					current = current->next;
				new_node->next = current->next;
				current->next = new_node;
			}
		}
		else
		{
			new_node->next = current->next;
			current->next = new_node;
		}
	}
}

void						insertionSort(t_files **head, t_flags flags)
{
	t_files				*sorted;
	t_files				*current;
	t_files				*next;

	sorted = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (flags.t == TRUE)
			sortedInsertTime(&sorted, current);
		else
			sortedInsert(&sorted, current);
		current = next;
	}
	*head = sorted;
}