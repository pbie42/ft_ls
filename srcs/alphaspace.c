/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alphaspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:16:01 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:09:41 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void							ft_alphastrsortbis(t_main *m, int i, int j)
{
	char						*temp;

	temp = (char *)malloc(sizeof(char) * ft_strlen(m->ptr[i]) + 1);
	ft_strcpy(temp, m->ptr[i]);
	ft_strcpy(m->ptr[i], m->ptr[j]);
	ft_strcpy(m->ptr[j], temp);
	free(temp);
}

void							ft_alphastrsort(t_main *m)
{
	int						i;
	int						j;

	i = 0;
	while (i < m->num_files - 1)
	{
		j = i + 1;
		while (j < m->num_files)
		{
			if (m->f.sm_r == TRUE && m->f.lg_r == FALSE)
			{
				if (ft_strcmp(m->ptr[i], m->ptr[j]) < 0)
					ft_alphastrsortbis(m, i, j);
			}
			else
			{
				if (ft_strcmp(m->ptr[i], m->ptr[j]) > 0)
					ft_alphastrsortbis(m, i, j);
			}
			j++;
		}
		i++;
	}
}

void							ft_time_sort(t_main *m)
{
	int						i;
	int						j;

	i = 0;
	while (i < m->num_files - 1)
	{
		j = i + 1;
		while (j < m->num_files)
		{
			if (m->f.sm_r == TRUE && m->f.lg_r == FALSE)
			{
				if (ft_strcmp(m->ptr[i], m->ptr[j]) < 0)
					ft_alphastrsortbis(m, i, j);
			}
			else
			{
				if (ft_strcmp(m->ptr[i], m->ptr[j]) > 0)
					ft_alphastrsortbis(m, i, j);
			}
			j++;
		}
		i++;
	}
}