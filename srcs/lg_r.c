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

void							ft_makeR(t_files *tmp, char *curr_dir, t_flags flags)
{
	ft_putendl("makeR");
	if (S_ISDIR((tmp)->st_mode))
	{
		if (((tmp)->dptr->d_name[0] == '.'
			&& strcmp((tmp)->dptr->d_name, ".")
			&& strcmp((tmp)->dptr->d_name, "..")))
			(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->name), flags);
	}
}

void							ft_printR(t_files *tmp, t_flags flags)
{
	if (flags.l == TRUE)
	{
		ft_printpermissions((tmp)->stat);
		ft_printinfo((tmp)->stat);
		ft_printtime((tmp)->stat);
	}
	if (!access((const char*)(tmp)->dptr->d_name, X_OK)) //if you do it like this one
	{
		if (S_ISDIR((tmp)->st_mode))
		{
			ft_foldercolorR((tmp)->name);
			// ft_putendl("\n");
			// if ((tmp)->dptr->d_name[0] != '.')
			// if (ft_strcmp((tmp)->dptr->d_name, ".")
			// 	&& ft_strcmp((tmp)->dptr->d_name, ".."))
			// 	(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->name), flags);
		}
		else
			ft_execcolorR((tmp)->name);
	}
	if (!access((const char*)(tmp)->dptr->d_name, X_OK))
		ft_execcolorR((tmp)->name);
	else
		ft_putendl((tmp)->name);
}

// t_files						*ft_list(char *curr_dir, t_flags flags)
// {
// 	DIR						*ds;
// 	struct dirent			*dptr;
// 	t_files					*files;
// 	t_files					*tmp;

// 	files = NULL;
// 	if(!(ds = opendir(curr_dir)))
// 		return (NULL);
// 	if(!(dptr = readdir(ds)))
// 		return (NULL);
// 	if(!flags.a)
// 		while((dptr = readdir(ds)) && dptr->d_name[0] == '.')
// 			ft_putchar('\0');
// 	if(!(files = ft_listnew(dptr, curr_dir)))
// 		return (NULL);
// 	// ft_putchar('\n');
// 	// ft_putendl(curr_dir);
// 	while((dptr = readdir(ds)))
// 		ft_lpb(&files, dptr, curr_dir);
// 	// We do this because we are going to want to return the start of the list
// 	// and if we iterate over it we will return the end of the list because we will
// 	// have lost the head of the list address
// 	tmp = files;
// 	while (tmp->next)
// 	{
// 		ft_putendl((tmp)->name);
// 		if (S_ISDIR((tmp)->st_mode)) //Problem is here
// 		{
// 				if (((tmp)->dptr->d_name[0] == '.'
// 					&& strcmp((tmp)->dptr->d_name, ".") != 0
// 					&& strcmp((tmp)->dptr->d_name, "..") != 0)
// 					|| (tmp)->dptr->d_name[0] != '.')
// 					(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->name), flags);
// 		}
// 		tmp = tmp->next;
// 	}
// 	// ft_makeR(tmp, curr_dir, flags);
// 	free(tmp);
// 	return files;
// }

t_files						*ft_list(char *curr_dir, t_flags flags)
{
	DIR						*ds;
	struct dirent			*dptr;
	t_files					*files;
	t_files					*tmp;
	t_files					*tmp2;

	files = NULL;

	if(flags.a)
		ft_putchar('\0');
	if(!(ds = opendir(curr_dir)))
		return (NULL);
	if(!(dptr = readdir(ds)))
		return (NULL);
	if(!flags.a)
		while((dptr = readdir(ds)) && dptr->d_name[0] == '.')
			ft_putchar('\0');
	if(!(files = ft_listnew(dptr, curr_dir)))
		return (NULL);
	while((dptr = readdir(ds)))
		ft_lpb(&files, dptr, curr_dir);
	// We do this because we are going to want to return the start of the list
	// and if we iterate over it we will return the end of the list because we will
	// have lost the head of the list address
	tmp = files;
	tmp2 = files;
	while (tmp->next)
	{
		if (S_ISDIR((tmp)->st_mode))
			ft_foldercolorR((tmp)->name);
		else if (((tmp)->st_mode > 0) && (S_IEXEC & (tmp)->st_mode))
			ft_execcolorR((tmp)->name);
		else if (S_ISREG((tmp)->st_mode))
			ft_putendl((tmp)->name);
		else
			ft_putchar('\n');
		tmp = tmp->next;
	}
	if (S_ISDIR((tmp)->st_mode))
		ft_foldercolorR((tmp)->name);
	else if (((tmp)->st_mode > 0) && (S_IEXEC & (tmp)->st_mode))
		ft_execcolorR((tmp)->name);
	else if (S_ISREG((tmp)->st_mode))
		ft_putendl((tmp)->name);
	else
		ft_putchar('\n');
	while (tmp2->next)
	{
		if (S_ISDIR((tmp2)->st_mode))
		{
			if (((tmp2)->dptr->d_name[0] == '.'
			&& strcmp((tmp2)->dptr->d_name, ".") != 0
			&& strcmp((tmp2)->dptr->d_name, "..") != 0)
			|| (tmp2)->dptr->d_name[0] != '.')
			{
				ft_putchar('\n');
				ft_putendl(make_path_fl(curr_dir, (tmp2)->name));
				(tmp2)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp2)->name), flags);
			}
		}
		tmp2 = tmp2->next;
	}
	
	free(tmp);
	return files;
}
