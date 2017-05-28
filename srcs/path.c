/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:16:01 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:09:41 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char					*make_path_fl(char *dir, char *file)
{
	char				*nw_path;
	size_t			l;

	// ft_putendl("making new path");
	l = ft_strlen(dir) + ft_strlen(file);
	l += 1;
	nw_path = NULL;
	if (!(nw_path = (char*)malloc(sizeof(char) * l)))
		return (NULL);
	nw_path = ft_strcpy(nw_path, dir);
	nw_path = ft_strcat(nw_path, "/");
	nw_path = ft_strcat(nw_path, file);
	return (nw_path);
}
