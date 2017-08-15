/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2017/08/10 17:12:12 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void						ft_init_flags(t_flags *f)
{
	f->l = FALSE;
	f->a = FALSE;
	f->t = FALSE;
	f->sm_r = FALSE;
	f->lg_r = FALSE;
	f->f = FALSE;
	f->g = FALSE;
	f->u = FALSE;
}

void						ft_flag_errors(char c, char *s, int x)
{
	if (x == 1)
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(c);
		ft_putchar('\n');
		ft_putendl("usage: ls [-Ralrtfgu] [file ...]");
		ft_exit("fail");
	}
	else
	{
		ft_putstr("ls: ");
		ft_putstr(s);
		ft_putendl(": No such file or directory");
	}
}

void						ft_flags(char *flags, t_flags *f, int x)
{
	if (flags[x] == 'l')
		f->l = TRUE;
	else if (flags[x] == 'a')
		f->a = TRUE;
	else if (flags[x] == 't')
		f->t = TRUE;
	else if (flags[x] == 'r')
		f->sm_r = TRUE;
	else if (flags[x] == 'R')
		f->lg_r = TRUE;
	else if (flags[x] == 'g')
	{
		f->g = TRUE;
		f->l = TRUE;
	}
	else if (flags[x] == 'u')
		f->u = TRUE;
	else if (flags[x] == 'f')
	{
		f->f = TRUE;
		f->a = TRUE;
	}
	else
		ft_flag_errors(flags[x], "nothing", 1);
}

void						ft_which_flags(char *flags, t_flags *f)
{
	int						x;

	x = 1;
	while (flags[x] != '\0')
	{
		ft_flags(flags, f, x);
		x++;
	}
}

t_start						ft_find_flags(char **av, t_flags *f)
{
	t_bool					flag;
	int						x;
	t_start					start;

	x = 0;
	start.selected = 0;
	start.start = 1;
	flag = TRUE;
	while (av[++x] != NULL)
	{
		if (av[x][0] == '-' && flag == TRUE)
			ft_which_flags(av[x], f);
		else if (av[x][0] != '-' && flag == TRUE)
		{
			flag = FALSE;
			start.start = x;
		}
		else if (av[x][0] == '-' && flag == FALSE)
			ft_flag_errors('x', av[x], 2);
		else
			flag = FALSE;
		if (av[x][0] != '-')
			start.selected++;
	}
	return (start);
}
