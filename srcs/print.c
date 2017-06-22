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

void							ft_printinfo(struct stat st)
{
	struct passwd		*pt;
	struct group		*p;

	//Print the number of hard links
	ft_putnbr((int)st.st_nlink);
	ft_putchar(' ');
	//Get the user name
	pt = getpwuid(st.st_uid);
	ft_putstr(pt->pw_name);
	ft_putchar(' ');
	//Get the group name
	p = getgrgid(st.st_gid);
	ft_putstr(p->gr_name);
	ft_putchar(' ');
	//Get the file size
	ft_putnbr((long long)st.st_size);
	ft_putchar(' ');
}

void							ft_printtime(struct stat st)
{
	int						c;
	char						date_time[100];

	//Get the date and time. We will have to remove the trailing newline.
	ft_memset(date_time, 0, sizeof(date_time));
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
