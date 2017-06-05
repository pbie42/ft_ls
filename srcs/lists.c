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
	return (alist);
}
