/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2016/06/28 15:16:26 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files					*ft_list_single(char *path, char *name)
{
	t_files				*alist;
	struct stat			fstat;
	char					*nw_path;

	nw_path = make_path_fl(path, name);
	if (lstat(nw_path, &fstat) < 0)
		return (ft_select_check(name));
	free(nw_path);
	if (!(alist = (t_files *)malloc(sizeof(t_files)))){
		return (NULL);}
	alist->next = NULL;
	alist->sub_dir = NULL;
	alist->stat = fstat;
	alist->mtime = fstat.st_mtime;
	alist->atime = fstat.st_atime;
	alist->st_mode = fstat.st_mode;
	alist->st_nlink = fstat.st_nlink;
	alist->st_uid = fstat.st_uid;
	alist->st_gid = fstat.st_gid;
	alist->st_size = fstat.st_size;
	alist->st_ino = fstat.st_ino;
	alist->st_blocks = fstat.st_blocks;
	alist->name = ft_strdup(name);
	return (alist);
}

void						ft_select_bis(t_files *tmp2, char *pwd, t_flags flags)
{
	struct stat			fstat;
	char					*nw_path;

	nw_path = make_path_fl(pwd, tmp2->name);
	if (lstat(nw_path, &fstat) < 0)
	{
		ft_putstr("ls: ");
		ft_putstr(tmp2->name);
		ft_putendl(": No such file or directory");
	}
	if (!S_ISDIR(tmp2->st_mode))
		ft_printR(tmp2, flags);
}

void						ft_select_ter(t_files *tmp, char *pwd, t_flags flags)
{
	struct stat			fstat;
	char					*nw_path;

	nw_path = make_path_fl(pwd, tmp->name);
	if (lstat(nw_path, &fstat) < 0)
	{
		ft_putstr("ls: ");
		ft_putstr(tmp->name);
		ft_putendl(": No such file or directory");
	}
	else
	{
		if (S_ISDIR(tmp->st_mode))
		{
			ft_putchar('\n');
			ft_putendl(nw_path);
			ft_list(nw_path, flags);
		}
	}
}

t_files					*ft_select_setup(char **av, t_files *file, char *pwd, int x)
{
	t_files				*tmp;
	t_files				*tmp2;

	tmp = NULL;
	if (file == NULL && av[x] != NULL)
		file = ft_list_single(pwd, av[x++]);
	tmp = file;
	while (av[x] != NULL)
	{
		tmp2 = ft_list_single(pwd, av[x]);
		if (tmp2 != NULL)
		{
			file->next = tmp2;
			file = file->next;
		}
		x++;
	}
	return (tmp);
}

void						ft_select(char *pwd, char **av, t_flags flags, int start)
{
	t_files				*file;
	t_files				*tmp;
	t_files				*tmp2;

	file = ft_list_single(pwd, av[start++]);
	if ((tmp = ft_select_setup(av, file, pwd, start)) == NULL)
		ft_exit(NULL);
	if (flags.f == FALSE)
		insertionSort(&tmp, flags);
	if (flags.sm_r == TRUE)
		tmp = reverse_lst(tmp);
	tmp2 = tmp;
	while (tmp2->next)
	{
		ft_select_bis(tmp2, pwd, flags);
		tmp2 = tmp2->next;
	}
	ft_select_bis(tmp2, pwd, flags);
	while (tmp->next)
	{
		ft_select_ter(tmp, pwd, flags);
		tmp = tmp->next;
	}
	ft_select_ter(tmp, pwd, flags);
}