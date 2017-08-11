/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:44:33 by pbie              #+#    #+#             */
/*   Updated: 2017/08/10 16:38:25 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					*ft_select_check(char *name)
{
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putendl(": No such file or directory");
	return (NULL);
}

void					ft_is_directory(t_files *tmp, char *curr_dir, t_flags f)
{
	char				*new_path;

	if (S_ISDIR((tmp)->st_mode))
		if (((tmp)->name[0] == '.' && ft_strcmp((tmp)->name, ".") != 0
		&& ft_strcmp((tmp)->name, "..") != 0) || (tmp)->name[0] != '.')
		{
			new_path = make_path_fl(curr_dir, (tmp)->name);
			if (!f.a)
			{
				if (tmp->name[0] != '.')
				{
					ft_putchar('\n');
					ft_putendl(new_path);
					(tmp)->sub_dir = ft_list(new_path, f);
				}
			}
			else
			{
				ft_putchar('\n');
				ft_putendl(new_path);
				(tmp)->sub_dir = ft_list(new_path, f);
			}
			free(new_path);
		}
}

void					ft_symlink_path(t_files *file, char *path, t_flags f)
{
	char				buf[1024];
	char				*link;
	ssize_t				link_size;
	ssize_t				attr_size;
	size_t				l;

	link_size = 0;
	attr_size = 0;
	link_size = readlink(path, buf, sizeof(buf));
	buf[link_size] = '\0';
	if (f.l == TRUE)
	{
		l = ft_strlen(" -> ") + ft_strlen(buf);
		if (!(link = (char*)malloc(sizeof(char) * l + 1)))
			ft_exit("error in malloc link");
		link = ft_strcpy(link, " -> ");
		if (ft_strlen(buf) == 0)
			file->link = ft_strjoin(link, ft_strjoin("private/", path));
		else
			file->link = ft_strjoin(link, buf);
		free(link);
	}
}
