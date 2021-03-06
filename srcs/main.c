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

int						main(int ac, char **av)
{
	t_start				start;
	t_files				*files;
	t_main				main;

	main.pwd = ft_strdup(".");
	ft_init_flags(&main.flags);
	if (ac > 1)
		start = ft_find_flags(av, &main.flags);
	main.start = start.start;
	if (start.selected != 0)
		ft_select(av, main);
	else
	{
		if (!(files = ft_list(".", main.flags)))
			ft_exit("\0");
		if (main.flags.lg_r)
			ft_free_r(files);
		else
			ft_free_lst(files);
	}
	return (0);
}
