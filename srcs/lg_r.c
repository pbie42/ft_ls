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
	t_files					*files;
	t_files					*tmp;
	// int						num_files;

	files = NULL;
	// tmp = NULL;

	// ft_putendl("LG-R Entered");
	// ft_putstr("current dir :");
	// ft_putendl(curr_dir);
	// ft_putnbr(ft_pwdcheck(curr_dir));
	// ft_putendl("\n");
	if(!(ds = opendir(curr_dir)))
		return (NULL);
	if(!(dptr = readdir(ds)))
		return (NULL);
	if(!(files = ft_listnew(dptr, curr_dir)))
		return (NULL);
	// ft_putendl("DONE WITH LIST NEW");
	while((dptr = readdir(ds)) != NULL)
	{
		ft_putendl("going to lpb");
		// ft_putstr("cd :");
		// ft_putendl(curr_dir);
		ft_putendl(dptr->d_name);
		ft_lpb(&files, dptr, curr_dir);
		// ft_putendl("out of ft_lpb!!!!!!!!!!!!!!!!!");
	}
	// We do this because we are going to want to return the start of the list
	// and if we iterate over it we will return the end of the list because we will
	// have lost the head of the list address
	// ft_putendl("out of while");
	// ft_putendl("\n");
	// ft_putendl("Going into while");
	tmp = files;
	while (tmp->next)
	{
		ft_putendl("yo");
		// ft_putstr("d name:");
		// ft_putendl((tmp)->dptr->d_name);
		if (!access((const char*)(tmp)->dptr->d_name, X_OK))
		{
			if (S_ISDIR((tmp)->st_mode))
			{
				ft_foldercolorR((tmp)->dptr->d_name);
				ft_putendl("IN IT");
				ft_putendl(curr_dir);
				// ft_putstr("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				ft_putendl("\n");
				if ((tmp)->dptr->d_name[0] != '.')
					(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->dptr->d_name));
				ft_putendl("OUT IT");
			}
			else
			{
				//If executable print in magenta
				ft_execcolorR((tmp)->dptr->d_name);
			}
		}
		else
		{
			//If normal print as default
			// ft_putendl("in the else");
			ft_putendl((tmp)->dptr->d_name);
		}
		// ft_putendl("going to next");
		tmp = tmp->next;
	}
	if (!access((const char*)(tmp)->dptr->d_name, X_OK))
		{
			if (S_ISDIR((tmp)->st_mode))
			{
				ft_foldercolorR((tmp)->dptr->d_name);
				// ft_putendl("IN IT");
				// ft_putendl(curr_dir);
				// ft_putstr("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				// ft_putendl("\n");
				if ((tmp)->dptr->d_name[0] != '.')
					(tmp)->sub_dir = ft_list(make_path_fl(curr_dir, (tmp)->dptr->d_name));
				// ft_putendl("OUT IT");
			}
			else
			{
				//If executable print in magenta
				ft_execcolorR((tmp)->dptr->d_name);
			}
		}
		else
		{
			//If normal print as default
			// ft_putendl("in the else");
			ft_putendl((tmp)->dptr->d_name);
		}
	free(tmp);
	return files;
}
