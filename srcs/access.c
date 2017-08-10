/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2017/08/10 15:57:32 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				sorted_access_time_b(t_files *current, t_files *new_node)
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
				&& current->next->atime - new_node->atime == 0)
			current = current->next;
		new_node->next = current->next;
		new_node->prev = current->prev;
		current->next = new_node;
	}
}

void				sorted_access_time(t_files **head, t_files *new_node)
{
	t_files			*curr;

	if (*head == NULL || (*head)->atime - new_node->atime < 0)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		curr = *head;
		while (curr->next != NULL
				&& curr->next->atime - new_node->atime > 0)
			curr = curr->next;
		if (curr->next != NULL && curr->next->atime - new_node->atime == 0)
			sorted_access_time_b(curr, new_node);
		else
		{
			new_node->next = curr->next;
			new_node->prev = curr->prev;
			curr->next = new_node;
		}
	}
}
