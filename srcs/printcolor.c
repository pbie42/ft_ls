/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 14:23:16 by pbie              #+#    #+#             */
/*   Updated: 2016/05/18 17:15:42 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_folder_color_r(char *ptr)
{
	ft_putstr(CYAN);
	ft_putstr(ptr);
	ft_putstr(STOP);
	// if (flags.l == TRUE)
		ft_putchar('\n');
	// else
	// {
	// 	if (tmp->next)
	// 		ft_putstr("     ");
	// }
}

void			ft_exec_color_r(char *ptr)
{
	ft_putstr(RED);
	ft_putstr(ptr);
	ft_putstr(STOP);
	// if (flags.l == TRUE)
		ft_putchar('\n');
	// else
	// {
	// 	if (tmp->next)
	// 		ft_putstr("     ");
	// }
}

void			ft_symlinkcolor(t_files *file, t_flags flags)
{
	ft_putstr(MAGENTA);
	ft_putstr(file->name);
	ft_putstr(STOP);
	if (flags.l == TRUE)
		ft_putstr(file->link);
	ft_putchar('\n');
	// else
	// {
	// 	if (file->next)
	// 		ft_putstr("     ");
	// }
}
