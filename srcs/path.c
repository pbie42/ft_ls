/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:16:01 by pbie              #+#    #+#             */
/*   Updated: 2017/08/10 18:05:13 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				*make_path_fl(char *dir, char *file)
{
	char			*nw_path;
	size_t			l;

	l = ft_strlen(dir) + ft_strlen(file);
	l += 1;
	nw_path = NULL;
	if (!(nw_path = (char*)malloc(sizeof(char) * l + 1)))
		return (NULL);
	if (file[0] == '/' || file[0] == '~')
		nw_path = ft_strdup(file);
	else
	{
		nw_path = ft_strcpy(nw_path, dir);
		nw_path = ft_strcat(nw_path, "/");
		nw_path = ft_strcat(nw_path, file);
	}
	return (nw_path);
}
