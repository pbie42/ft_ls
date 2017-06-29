/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:44:33 by pbie              #+#    #+#             */
/*   Updated: 2016/05/13 19:01:46 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void								*ft_select_check(char *name)
{
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putendl(": No such file or directory");
	return (NULL);
}

void								ft_symlink_path(t_files *file, char *path, t_flags f)
{
	char							buf[1024];
	ssize_t						link_size;
	ssize_t						attr_size;
	size_t						l;

	link_size = 0;
	attr_size = 0;
	link_size = readlink(path, buf, sizeof(buf));
	buf[link_size] = '\0';
	if (f.l == TRUE)
	{
		l = ft_strlen(" -> ") + ft_strlen(buf);
		if (!(file->link = (char*)malloc(sizeof(char) * l + 1)))
			ft_exit("error in malloc link");
		file->link = ft_strcpy(file->link, " -> ");
		file->link = ft_strjoin(file->link, buf);
	}
	//	attr_size = lgetxattr(file->path, buf, value, link_size);
}
