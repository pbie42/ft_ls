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
	// t_files				*list;
	t_files				*curr;
	t_files				*prev;
	t_files				*new;

	new = ft_listnew(dptr, pwd);
	curr = NULL;
	prev = NULL;

	ft_putendl("lpb entered");
	if (!*b_lst)
	{
		ft_putendl("this is happening");
		*b_lst = ft_listnew(dptr, pwd);
		return ;
	}
	curr = *b_lst;

	ft_putendl("else ft_lpb entered");
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		ft_putendl("after");
		ft_putchar('\n');
	}
	ft_putendl("out while lpb");
	// ft_putendl(pwd);
	prev->next = new;
	new->next = curr;
	ft_putendl("\n");
	// free(list);
}

t_files					*ft_listnew(struct dirent *dptr, char *path)
{
	t_files				*alist;
	struct stat			fstat;
	char					*nw_path;

	ft_putendl("ENTERED LISTNEW");
	// ft_putendl("\n");
	// ft_putstr("old path: ");
	// ft_putendl(path);
	nw_path = make_path_fl(path, dptr->d_name);
	// ft_putendl("going into stat");
	// ft_putstr("new path :");
	// ft_putendl(nw_path);
	if (lstat(nw_path, &fstat) < 0)
	{
		ft_putendl("path is null homie");
		return (NULL);
	}
	// ft_putendl("goin to free");
	free(nw_path);
	if (!(alist = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
	alist->next = NULL;
	alist->sub_dir = NULL;
	alist->mtime = fstat.st_mtime;
	alist->st_mode = fstat.st_mode;
	alist->st_nlink = fstat.st_nlink;
	alist->st_uid = fstat.st_uid;
	alist->st_gid = fstat.st_gid;
	alist->st_size = fstat.st_size;
	alist->st_ino = fstat.st_ino;
	alist->st_blocks = fstat.st_blocks;
	alist->dptr = dptr;
	ft_putendl("returning alist");
	// ft_putendl("\n");
	return (alist);
}
