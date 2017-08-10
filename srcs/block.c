/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 13:17:17 by pbie              #+#    #+#             */
/*   Updated: 2017/08/10 16:31:11 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					ft_print_block(int block, t_flags flags)
{
	if (flags.l == TRUE)
	{
		ft_putstr("total ");
		ft_putnbr(block);
		ft_putchar('\n');
	}
}

void					*ft_setup_block(char *curr_dir, t_flags flags, t_r *r)
{
	if (!(r->ds = opendir(curr_dir)))
		ft_exit(strerror(errno));
	if (!(r->dptr = readdir(r->ds)))
		ft_exit("readdir problem");
	if (!(r->files = ft_listnew(r->dptr, curr_dir, flags)))
		ft_exit("listnew problem");
	while ((r->dptr = readdir(r->ds)))
		ft_lpb(&r->files, r->dptr, curr_dir, flags);
	return (r->files);
}

void					ft_block(char *curr_dir, t_flags flags)
{
	t_r					r;
	int					block;
	t_files				*tmp;

	block = 0;
	r.ds = NULL;
	r.files = NULL;
	r.dptr = NULL;
	ft_setup_block(curr_dir, flags, &r);
	tmp = r.files;
	while (r.files->next)
	{
		if (ft_strcmp(r.files->name, ".") != 0 && ft_strcmp(r.files->name, "..")
			!= 0 && r.files->name[0] == '.' && flags.a != TRUE)
			r.files = r.files->next;
		else
		{
			block += (int)r.files->st_blocks;
			r.files = r.files->next;
		}
	}
	block += (int)r.files->st_blocks;
	closedir(r.ds);
	ft_free_lst(tmp);
	ft_print_block(block, flags);
}
