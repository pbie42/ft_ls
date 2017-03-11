/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 16:44:33 by pbie              #+#    #+#             */
/*   Updated: 2016/05/13 19:01:46 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int								ft_pwdcheck(char *curr_dir)
{
	if (curr_dir == NULL)
	{
		ft_putstr("Error: Could not get the working directory");
		ft_putchar('\n');
		return (1);
	}
	else
		return (0);
}

int								ft_dircheck(DIR *dp)
{
	if (dp == NULL)
	{
		ft_putstr("Error: Could not open the working directory");
		ft_putchar('\n');
		free(dp);
		return (1);
	}
	else
		return (0);
}
