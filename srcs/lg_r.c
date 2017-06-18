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

void							ft_list_bis(t_files *files, char *curr_dir, t_flags flags)
{
	t_files					*tmp;
	char						*newPath;

	tmp = files;
	while (tmp->next)
	{
		if (S_ISDIR((tmp)->st_mode))
		{
			if (((tmp)->name[0] == '.'
			&& ft_strcmp((tmp)->name, ".") != 0
			&& ft_strcmp((tmp)->name, "..") != 0)
			|| (tmp)->name[0] != '.')
			{
				newPath = make_path_fl(curr_dir, (tmp)->name);
				ft_putchar('\n');
				ft_putendl(newPath);
				(tmp)->sub_dir = ft_list(newPath, flags);
				free(tmp);
			}
		}
		tmp = tmp->next;
	}
}

void							ft_printType(t_files *tmp)
{
	if (S_ISDIR((tmp)->st_mode))
		ft_foldercolorR((tmp)->name);
	else if (((tmp)->st_mode > 0) && (S_IEXEC & (tmp)->st_mode))
		ft_execcolorR((tmp)->name);
	else if (S_ISREG((tmp)->st_mode))
		ft_putendl((tmp)->name);
	else
		ft_putchar('\0');
}

void							ft_printR(t_files *tmp, t_flags flags)
{
	if (flags.l == TRUE)
	{
		ft_printpermissions(tmp->stat);
		ft_printinfo(tmp->stat);
		ft_printtime(tmp->stat);
	}
	ft_printType(tmp);
}

t_files						*ft_list(char *curr_dir, t_flags flags)
{
	DIR						*ds;
	struct dirent			*dptr;
	t_files					*files;
	t_files					*tmp;

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
	tmp = files;
	while (tmp->next)
	{
		ft_printR(tmp, flags);
		tmp = tmp->next;
	}
	ft_printR(tmp, flags);
	ft_list_bis(files, curr_dir, flags);
	free(tmp);
	return files;
}
