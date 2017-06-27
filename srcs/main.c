/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:16:01 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:09:41 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// int							ft_num_files(DIR *ds, t_flags f)
// {
// 	struct dirent			*dptr;
// 	int						num_files;

// 	num_files = 0;
// 	while ((dptr = readdir(ds)) != NULL)
// 	{
// 		if (f.a == TRUE && dptr->d_name[0] == '.')
// 			num_files++;
// 		if (dptr->d_name[0] != '.')
// 			num_files++;
// 	}
// 	return (num_files);
// }

char							**ft_ptr_malloc(int num_files)
{
	char						**ptr;

	//Allocate memory to hold the addresses of the names of contents in current
	//working directory
	ptr = (char**)malloc(sizeof(char *) * num_files + 1);
	if (ptr == NULL)
	{
		ft_putstr("Memory allocation failed");
		ft_exit("Oh No! The allocation failed!");
	}
	return (ptr);
}

// void							ft_ptrfill(t_main *m)
// {
// 	int						j;
// 	size_t					l;
// 	struct dirent			*dptr;

// 	j = 0;
// 	while ((dptr = readdir(m->ds)) != NULL)
// 	{
// 		l = ft_strlen(dptr->d_name) + 1;
// 		if (m->f.a == TRUE && dptr->d_name[0] == '.')
// 		{
// 			m->ptr[j] = ft_strndup(dptr->d_name, l);
// 			j++;
// 		}
// 		if (dptr->d_name[0] != '.')
// 		{
// 			m->ptr[j] = ft_strndup(dptr->d_name, l);
// 			j++;
// 		}
// 	}
// 	m->ptr[j] = NULL;
// 	closedir(m->ds);
// }

// int								ft_pwd(t_main *m)
// {
// 	//Get the string value of the Present Working Directory
// 	m->curr_dir = getenv("PWD");
// 	//Check to make sure the current directory isn't null
// 	if (ft_pwdcheck(m->curr_dir))
// 		return (-1);
// 	//Open the current directory
// 	m->ds = opendir((const char*)m->curr_dir);
// 	if (ft_dircheck(m->ds))
// 		return (-1);
// 	// We pass the directory stream and the flags struct in our main struct to
// 	// num files to get the number of files with regards to our flags
// 	m->num_files = ft_num_files(m->ds, m->f);
// 	//We are counting the number of files/folders inside the current working
// 	//directory. When it's done we close the directory stream.
// 	closedir(m->ds);
// 	return (0);
// }

// int								ft_num_file_check(t_main *m)
// {
// 	//We then check that we should have at least one file/folder inside the
// 	//current working directory
// 	if (!m->num_files)
// 		return (-1);
// 	else
// 		m->ptr = ft_ptr_malloc(m->num_files);

// 	//Now we open the directory again

// 	m->ds = opendir((const char*)m->curr_dir);
// 	if (ft_dircheck(m->ds))
// 		return (-1);
// 	return (0);
// }

t_files					*ft_list_single(char *path, char *name)
{
	t_files				*alist;
	struct stat			fstat;
	char					*nw_path;

	nw_path = make_path_fl(path, name);
	if (lstat(nw_path, &fstat) < 0)
		return (NULL);
	free(nw_path);
	if (!(alist = (t_files *)malloc(sizeof(t_files))))
		return (NULL);
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

void									ft_selected(char *pwd, char **av, t_flags flags)
{
	// char								**selected;
	char								*nw_path;
	struct stat						fstat;
	int								x;
	t_files							*file;

	x = 1;
	while (av[x] != NULL)
	{
		nw_path = make_path_fl(pwd, av[x]);
		if(av[x][0] != '-')
		{
			if (lstat(nw_path, &fstat) < 0)
			{
				ft_putstr("ls: ");
				ft_putstr(av[x]);
				ft_putendl(": No such file or directory");
			}
			else
			{
				file = ft_list_single(pwd, av[x]);
				if (S_ISDIR((file)->st_mode))
				{
					ft_putchar('\n');
					ft_putendl(nw_path);
					ft_list(nw_path, flags);
				}
				else
					ft_printR(file, flags);
			}
		}
		x++;
	}
}

int									main(int ac, char **av)
{
	t_flags							flags;
	char								*pwd;
	int								selected;

	selected = 0;
	ft_init_flags(&flags);
	pwd = getenv("PWD");
	if (ac > 1)
		selected = ft_find_flags(av, &flags);
	if (selected != 0)
		ft_selected(pwd, av, flags);
	else
		ft_list(pwd, flags);
	return (0);
}
