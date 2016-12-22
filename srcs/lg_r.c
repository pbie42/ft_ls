/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lg_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:19:09 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files           *ft_list(char *name)
{
  DIR             *dir;
  t_files         *fls;
  struct dirent   *ent;
  t_files         *tmp;

  fls = NULL;

  if(!(dir = opendir(name)))
    return (NULL);
  if(!(ent = readdir(dir)))
    return (NULL);
  if(!(fls = ft_lstnew(ent, name)))
    return (NULL);
  while((ent = readdir(dir)))
  {
    ft_list_push_back(&fls, ent, name);
  }
  //We do this because we are going to want to return the start of the list
  //and if we iterate over it we will return the end of the list;
  tmp = fls;
  while (tmp)
  {
    
  }
}
