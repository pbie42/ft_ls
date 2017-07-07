/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:16:01 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:09:41 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void							ft_printinfo(struct stat st, t_flags flags)
{
	struct passwd		*pt;
	struct group		*p;

	ft_putnbr((int)st.st_nlink);
	ft_putchar(' ');
	if (flags.g == FALSE)
	{
		pt = getpwuid(st.st_uid);
		ft_putstr(pt->pw_name);
		ft_putchar(' ');
	}
	p = getgrgid(st.st_gid);
	ft_putstr(p->gr_name);
	ft_putchar(' ');
	ft_putnbr((long long)st.st_size);
	ft_putchar(' ');
}

void							ft_printtime(struct stat st, t_flags flags)
{
	int						c;
	char						date_time[100];

	ft_memset(date_time, 0, sizeof(date_time));
	if (flags.u == TRUE)
		ft_strncpy(date_time, ctime(&st.st_atime), sizeof(date_time));
	else
		ft_strncpy(date_time, ctime(&st.st_mtime), sizeof(date_time));
	c = 0;
	while (date_time[c] != '\0')
	{
		if (date_time[c] == '\n')
		{
			date_time[c] = '\0';
		}
		c++;
	}
	ft_putstr(date_time);
	ft_putchar(' ');
}

void							ft_printType(t_files *tmp, t_flags flags)
{
	if (S_ISDIR((tmp)->st_mode))
		ft_foldercolorR((tmp)->name);
	else if (S_ISLNK((tmp)->st_mode))
		ft_symlinkcolor(tmp, flags);
	else if (((tmp)->st_mode > 0) && (S_IEXEC & (tmp)->st_mode))
		ft_execcolorR((tmp)->name);
	else if (S_ISREG((tmp)->st_mode))
		ft_putendl((tmp)->name);
	else
		ft_putchar('\0');
}

void							ft_printR(t_files *tmp, t_flags flags)
{
	if (!flags.a)
	{
		if (tmp->name[0] != '.')
		{
			if (flags.l == TRUE)
			{
				ft_printpermissions(tmp->stat);
				ft_printinfo(tmp->stat, flags);
				ft_printtime(tmp->stat, flags);
			}
			ft_printType(tmp, flags);
		}
	}
	else
	{
		if (flags.l == TRUE)
		{
			ft_printpermissions(tmp->stat);
			ft_printinfo(tmp->stat, flags);
			ft_printtime(tmp->stat, flags);
		}
		ft_printType(tmp, flags);
	}
}
