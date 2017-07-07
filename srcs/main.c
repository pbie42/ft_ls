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
	t_flags				flags;
	t_start				start;
	t_files				*files;

	ft_init_flags(&flags);
	if (ac > 1)
		start = ft_find_flags(av, &flags);
	if (start.selected != 0)
		ft_select(".", av, flags, start.start);
	else
	{
		files = ft_list(".", flags);
		if (flags.lg_r)
			ft_free_R(files);
		else
			ft_free_lst(files);
	}
	return (0);
}
