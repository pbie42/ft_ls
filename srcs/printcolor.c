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

void			ft_foldercolor(char **ptr, int count)
{
	ft_putstr(CYAN);
	ft_putstr(ptr[count]);
	ft_putstr(STOP);
	ft_putchar('\n');
}

void			ft_execcolor(char **ptr, int count)
{
	ft_putstr(MAGENTA);
	ft_putstr(ptr[count]);
	ft_putstr(STOP);
	ft_putchar('\n');
}

void			ft_foldercolornorm(char **ptr, int count)
{
	ft_putstr(CYAN);
	ft_putstr(ptr[count]);
	ft_putstr(STOP);
	ft_putstr("   ");
}

void			ft_execcolornorm(char **ptr, int count)
{
	ft_putstr(MAGENTA);
	ft_putstr(ptr[count]);
	ft_putstr(STOP);
	ft_putstr("   ");
}

void			ft_normcolornorm(char **ptr, int count)
{
	ft_putstr(ptr[count]);
	ft_putstr("   ");
}

void			ft_foldercolorR(char *ptr)
{
	ft_putstr(CYAN);
	ft_putstr(ptr);
	ft_putstr(STOP);
	ft_putchar('\n');
}

void			ft_execcolorR(char *ptr)
{
	ft_putstr(MAGENTA);
	ft_putstr(ptr);
	ft_putstr(STOP);
	ft_putchar('\n');
}

void			ft_foldercolornormR(char *ptr)
{
	ft_putstr(CYAN);
	ft_putstr(ptr);
	ft_putstr(STOP);
	ft_putstr("   ");
}

void			ft_execcolornormR(char *ptr)
{
	ft_putstr(MAGENTA);
	ft_putstr(ptr);
	ft_putstr(STOP);
	ft_putstr("   ");
}

void			ft_normcolornormR(char *ptr)
{
	ft_putstr(ptr);
	ft_putstr("   ");
}
