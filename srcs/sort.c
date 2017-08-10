/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/22/06 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2017/08/10 18:51:33 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					sorted_insert(t_files **head, t_files *new_node)
{
	t_files				*current;

	if (*head == NULL || ft_strcmp((*head)->name, new_node->name) > 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL
				&& ft_strcmp(current->next->name, new_node->name) < 0)
		{
			current = current->next;
		}
		new_node->next = current->next;
		new_node->prev = current->prev;
		current->next = new_node;
	}
}

void					insertion_sort(t_files **head, t_flags flags)
{
	t_files				*sorted;
	t_files				*current;
	t_files				*next;

	sorted = NULL;
	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (flags.t == TRUE && flags.u == TRUE)
			sorted_access_time(&sorted, current);
		else if (flags.t == TRUE)
			sorted_insert_time(&sorted, current);
		else
			sorted_insert(&sorted, current);
		current = next;
	}
	*head = sorted;
}
