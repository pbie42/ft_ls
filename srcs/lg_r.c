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

t_files						*ft_list(char *curr_dir)
{
	DIR						*ds;
	struct dirent			*dptr;
	t_files					*fls;
	t_files					*tmp;

	fls = NULL;

	if(!(ds = opendir(curr_dir)))
		return (NULL);
	if(!(dptr = readdir(ds)))
		return (NULL);
	if(!(fls = ft_lstnew(dptr, curr_dir)))
		return (NULL);
	while((dptr = readdir(ds)))
	{
		ft_list_push_back(&fls, dptr, curr_dir);
	}
	//We do this because we are going to want to return the start of the list
	//and if we iterate over it we will return the end of the list;
	tmp = fls;
	while (tmp)
	{

	}
}
