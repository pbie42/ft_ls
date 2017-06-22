/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 18:21:05 by pbie              #+#    #+#             */
/*   Updated: 2016/02/10 17:06:14 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						ft_lpb(t_files **b_lst, struct dirent *dptr, char *pwd)
{
	t_files				*list;

	list = *b_lst;
	if (!list)
		list = ft_listnew(dptr, pwd);
	else
	{
		while ((list)->next)
			list = list->next;
		list->next = ft_listnew(dptr, pwd);
	}
}

t_files					*ft_listnew(struct dirent *dptr, char *path)
{
	t_files				*alist;
	struct stat			fstat;
	char					*nw_path;

	nw_path = make_path_fl(path, dptr->d_name);
	if (lstat(nw_path, &fstat) < 0)
		return (NULL);
	free(nw_path);
	if (!(alist = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	alist->next = NULL;
	alist->sub_dir = NULL;
	alist->stat = fstat;
	alist->mtime = fstat.st_mtime;
	alist->st_mode = fstat.st_mode;
	alist->st_nlink = fstat.st_nlink;
	alist->st_uid = fstat.st_uid;
	alist->st_gid = fstat.st_gid;
	alist->st_size = fstat.st_size;
	alist->st_ino = fstat.st_ino;
	alist->st_blocks = fstat.st_blocks;
	alist->dptr = dptr;
	alist->name = ft_strdup(dptr->d_name);
	// ft_putstr("     ");
	// ft_putendl(alist->name);
	return (alist);
}

t_files					*reverse_lst(t_files *head)
{
	t_files				*curr;
	t_files				*prev;
	t_files				*next;

	curr = head;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	return head;
}


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
		{
				current = current->next;
		}
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
				{
						current = current->next;
				}
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