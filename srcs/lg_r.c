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

void							ft_is_directory(t_files *tmp, char *curr_dir, t_flags flags)
{
	char						*newPath;

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
		}
	}
}

void							ft_list_b(t_files *files, char *curr_dir, t_flags flags)
{
	t_files					*tmp;

	tmp = files;
	while (tmp->next)
	{
		ft_is_directory(tmp, curr_dir, flags);
		tmp = tmp->next;
	}
	ft_is_directory(tmp, curr_dir, flags);
}

t_files						*ft_list(char *curr_dir, t_flags flags)
{
	t_r						r;
	t_files					*tmp;
	t_files					*tmp2;

	if(!(r.ds = opendir(curr_dir)))
		return (NULL);
	if(!(r.dptr = readdir(r.ds)))
		return (NULL);
	if(!flags.a)
		while((r.dptr = readdir(r.ds)) && r.dptr->d_name[0] == '.')
			ft_putchar('\0');
	if(!(r.files = ft_listnew(r.dptr, curr_dir)))
		return (NULL);
	while((r.dptr = readdir(r.ds)))
		ft_lpb(&r.files, r.dptr, curr_dir);
	tmp = r.files;
	insertionSort(&tmp, flags);
	if (flags.sm_r == TRUE)
	{
		tmp = reverse_lst(tmp);
		tmp2 = tmp;
	}
	else if (flags.t)
		tmp2 = tmp;
	else
		tmp2 = r.files;
	while (tmp->next)
	{
		ft_printR(tmp, flags);
		tmp = tmp->next;
	}
	ft_printR(tmp, flags);
	if (flags.lg_r == TRUE)
		ft_list_b(tmp2, curr_dir, flags);
	free(tmp);
	return r.files;
}
