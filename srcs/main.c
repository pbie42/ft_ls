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

int									main(int ac, char **av)
{
	struct dirent					*dptr;
	t_flags							flags;
	char								*pwd;
	t_files							*files;

	dptr = NULL;
	files = NULL;
	ft_init_flags(&flags);
	if (ac > 1 && av[1][0] == '-')
		ft_find_flags(av, &flags);
	pwd = getenv("PWD");
	ft_list(pwd, flags);
	return (0);
}
