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

void							ft_printR(t_files *tmp, char *curr_dir, t_flags flags)
{
	// if (flags.l == TRUE)
	// {
	// 	ft_printpermissions((tmp)->stat);
	// 	ft_printinfo((tmp)->stat);
	// 	ft_printtime((tmp)->stat);
	// }
	if (!access((const char*)(tmp)->dptr->d_name, X_OK))
	{
		if (S_ISDIR((tmp)->st_mode))
		{
			ft_foldercolorR((tmp)->name);
			// ft_putendl("\n");
			// if ((tmp)->dptr->d_name[0] != '.')
			if (ft_strcmp((tmp)->dptr->d_name, ".")
				&& ft_strcmp((tmp)->dptr->d_name, ".."))
				(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->name), flags);
		}
		else
			ft_execcolorR((tmp)->name);
	}
	else
		ft_putendl((tmp)->name);
}

t_files						*ft_list(char *curr_dir, t_flags flags)
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
	if(!flags.a)
		while((dptr = readdir(ds)) && dptr->d_name[0] == '.')
		{
			// ft_putendl("dis is happenin");
			ft_putchar('\0');
		}
	if(!(files = ft_listnew(dptr, curr_dir)))
		return (NULL);
	ft_putchar('\n');
	ft_putendl(curr_dir);
	while((dptr = readdir(ds)))
		ft_lpb(&files, dptr, curr_dir);
	// if(flags.a)
	// {
	// 	ft_putchar('\n');
	// 	ft_putendl(curr_dir);
	// 	while((dptr = readdir(ds)))
	// 		if (dptr->d_name[0] != '.')
	// 			ft_lpb(&files, dptr, curr_dir);
	// } else {
	// 	ft_putchar('\n');
	// 	ft_putendl(curr_dir);
	// 	while((dptr = readdir(ds)))
	// 		ft_lpb(&files, dptr, curr_dir);
	// }
	// We do this because we are going to want to return the start of the list
	// and if we iterate over it we will return the end of the list because we will
	// have lost the head of the list address
	tmp = files;
	while (tmp->next)
	{
		ft_printR(tmp, curr_dir, flags);
		tmp = tmp->next;
	}
	ft_printR(tmp, curr_dir, flags);
	free(tmp);
	return files;
}
