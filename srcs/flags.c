/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:19:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void							ft_init_flags(t_flags *f)
{
	f->l = FALSE;
	f->a = FALSE;
	f->t = FALSE;
	f->sm_r = FALSE;
	f->lg_r = FALSE;
}

void							ft_which_flags(char *ops, t_flags *f)
{
	int							x;

	x = 1;
	while (ops[x] != '\0')
	{
		if (ops[x] == 'l')
			f->l = TRUE;
		else if (ops[x] == 'a')
			f->a = TRUE;
		else if (ops[x] == 't')
			f->t = TRUE;
		else if (ops[x] == 'r')
			f->sm_r = TRUE;
		else if (ops[x] == 'R')
			f->lg_r = TRUE;
		else
		{
			ft_putstr("ls: illegal option -- ");
			ft_putchar(ops[x]);
			ft_putchar('\n');
			ft_putendl("usage: ls [-Ralrt] [file ...]");
			ft_exit("fail");
		}
		x++;
	}
}

void							ft_find_flags(char **av, t_flags *f)
{
	t_bool					opt;
	int							x;

	x = 1;
	opt = TRUE;
	while (av[x] != NULL)
	{
		ft_putendl("ft_find_options");
		if (av[x][0] == '-' && opt == TRUE)
			ft_which_flags(av[x], f);
		else if (av[x][0] != '-' && opt == TRUE)
			opt = FALSE;
		else if (av[x][0] == '-' && opt == FALSE)
		{
			ft_putstr("ls: ");
			ft_putstr(av[x]);
			ft_putendl(": No such file or directory");
		}
		else
			opt = FALSE;
		x++;
	}
}
