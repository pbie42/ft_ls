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

t_files					*ft_list_single(char *path, char *name, t_flags flags)
{
	t_single				s;

	s.nw_path = make_path_fl(path, name);
	if (lstat(s.nw_path, &s.fstat) < 0)
		return (ft_select_check(name));
	free(s.nw_path);
	if (!(s.alist = (t_files *)malloc(sizeof(t_files)))){
		return (NULL);}
	s.alist->next = NULL;
	s.alist->sub_dir = NULL;
	s.alist->stat = s.fstat;
	s.alist->mtime = s.fstat.st_mtime;
	s.alist->atime = s.fstat.st_atime;
	s.alist->st_mode = s.fstat.st_mode;
	s.alist->st_nlink = s.fstat.st_nlink;
	s.alist->st_uid = s.fstat.st_uid;
	s.alist->st_gid = s.fstat.st_gid;
	s.alist->st_size = s.fstat.st_size;
	s.alist->st_ino = s.fstat.st_ino;
	s.alist->st_blocks = s.fstat.st_blocks;
	s.alist->name = ft_strdup(name);
	if (S_ISLNK((s.alist)->st_mode))
		ft_symlink_path(s.alist, s.nw_path, flags);
	return (s.alist);
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

t_files					*ft_select_setup(char **av, t_files *file, char *pwd, int x, t_flags flags)
{
	t_files				*tmp;
	t_files				*tmp2;

	tmp = NULL;
	if (file == NULL && av[x] != NULL)
		file = ft_list_single(pwd, av[x++], flags);
	tmp = file;
	while (av[x] != NULL)
	{
		tmp2 = ft_list_single(pwd, av[x], flags);
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

	file = ft_list_single(pwd, av[start++], flags);
	if ((tmp = ft_select_setup(av, file, pwd, start, flags)) == NULL)
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