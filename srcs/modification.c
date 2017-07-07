/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2016/12/11 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						sortedInsertTime_b(t_files *current, t_files *new_node)
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
			new_node->prev = current->prev;
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
			sortedInsertTime_b(current, new_node);
		else
		{
			new_node->next = current->next;
			new_node->prev = current->prev;
			current->next = new_node;
		}
	}
}