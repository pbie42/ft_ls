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
		if (S_ISLNK((curr)->st_mode)){
			free(curr->link);}
		free (curr);
	}
}

void					ft_free_lst_rvrs(t_files *file)
{
	t_files			*curr;

	while ((curr = file) != NULL) { // set curr to head, stop if list empty.
		file = file->prev;          // advance head to next element.
		free(curr->name);
		// ft_putendl("freeing lst rvrs");
		if (S_ISLNK((curr)->st_mode)){
			// ft_putendl("freeing link rvs");
			free(curr->link);}
		free (curr);                // delete saved pointer.
	}
}

void					ft_free_R(t_files *file)
{
	t_files			*curr;

	while ((curr = file) != NULL)
	{ // set curr to head, stop if list empty.
		if (S_ISDIR((file)->st_mode))
		{
			if (((file)->name[0] == '.'
				&& ft_strcmp((file)->name, ".") != 0
				&& ft_strcmp((file)->name, "..") != 0)
				|| (file)->name[0] != '.')
				ft_free_R(file->sub_dir);
		}
		file = file->next;          // advance head to next element.
		free(curr->name);
		if (S_ISLNK((curr)->st_mode))
			free(curr->link);
		free (curr);                // delete saved pointer.
	}
}