/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 14:23:16 by pbie              #+#    #+#             */
/*   Updated: 2016/05/18 17:15:42 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_foldercolor(long *ptr, int count)
{
	ft_putstr(CYAN);
	ft_putstr((char*)ptr[count]);
	ft_putstr(STOP);
	ft_putchar('\n');
}

void			ft_execcolor(long *ptr, int count)
{
	ft_putstr(MAGENTA);
	ft_putstr((char*)ptr[count]);
	ft_putstr(STOP);
	ft_putchar('\n');
}

void			ft_foldercolornorm(long *ptr, int count)
{
	ft_putstr(CYAN);
	ft_putstr((char*)ptr[count]);
	ft_putstr(STOP);
	ft_putstr("   ");
}

void			ft_execcolornorm(long *ptr, int count)
{
	ft_putstr(MAGENTA);
	ft_putstr((char*)ptr[count]);
	ft_putstr(STOP);
	ft_putstr("   ");
}

void			ft_normcolornorm(long *ptr, int count)
{
	ft_putstr((char*)ptr[count]);
	ft_putstr("   ");
}