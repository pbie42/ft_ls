/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2017/07/06 15:19:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					ft_free_lst(t_files *file)
{
	t_files			*curr;

	while ((curr = file) != NULL)
	{
		file = file->next;
		free(curr->name);
		if (S_ISLNK((curr)->st_mode))
		{
			free(curr->link);
		}
		free(curr);
	}
}

void					ft_free_lst_rvrs(t_files *file)
{
	t_files			*curr;

	while ((curr = file) != NULL)
	{
		file = file->prev;
		free(curr->name);
		if (S_ISLNK((curr)->st_mode))
		{
			free(curr->link);
		}
		free(curr);
	}
}

void					ft_free_r(t_files *file)
{
	t_files			*curr;

	while ((curr = file) != NULL)
	{
		if (S_ISDIR((file)->st_mode))
		{
			if (((file)->name[0] == '.'
				&& ft_strcmp((file)->name, ".") != 0
				&& ft_strcmp((file)->name, "..") != 0)
				|| (file)->name[0] != '.')
				ft_free_r(file->sub_dir);
		}
		file = file->next;
		free(curr->name);
		if (S_ISLNK((curr)->st_mode))
			free(curr->link);
		free(curr);
	}
}
