/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lg_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:19:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files						*ft_list(char *curr_dir)
{
	DIR						*ds;
	struct dirent			*dptr;
	t_files					*files;
	t_files					*tmp;

	files = NULL;

	if(!(ds = opendir(curr_dir)))
		return (NULL);
	if(!(dptr = readdir(ds)))
		return (NULL);
	if(!(files = ft_listnew(dptr, curr_dir)))
		return (NULL);
	while((dptr = readdir(ds)))
		ft_lpb(&files, dptr, curr_dir);
	// We do this because we are going to want to return the start of the list
	// and if we iterate over it we will return the end of the list because we will
	// have lost the head of the list address
	tmp = files;
	while (tmp->next)
	{
		if (!access((const char*)(tmp)->dptr->d_name, X_OK))
		{
			if (S_ISDIR((tmp)->st_mode))
			{
				ft_foldercolorR((tmp)->name);
				ft_putendl("\n");
				if ((tmp)->dptr->d_name[0] != '.')
					(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->name));
			}
			else
				ft_execcolorR((tmp)->name);
		}
		else
			ft_putendl((tmp)->name);
		tmp = tmp->next;
	}
	if (!access((const char*)(tmp)->dptr->d_name, X_OK))
	{
		if (S_ISDIR((tmp)->st_mode))
		{
			ft_foldercolorR((tmp)->name);
			if ((tmp)->dptr->d_name[0] != '.')
				(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->name));
		}
		else
			ft_execcolorR((tmp)->name);
	}
	else
		ft_putendl((tmp)->name);
	free(tmp);
	return files;
}
