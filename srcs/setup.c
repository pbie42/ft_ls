/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 14:50:49 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 14:51:33 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int               ft_num_files(DIR *dp, t_flags f)
{
  struct dirent   *dptr;
  int             num_files;

  num_files = 0;
  while ((dptr = readdir(dp)) != NULL)
  {
    //Do not count the files beginning with '.'
    //TODO: will need to change this later on to include all files
    if (f.a == TRUE && dptr->d_name[0] == '.')
      num_files++;
    if (dptr->d_name[0] != '.')
      num_files++;
  }
  return (num_files);
}

char              **ft_ptr_malloc(int num_files)
{
  char            **ptr;

  //Allocate memory to hold the addresses of the names of contents in current
  //working directory
  ptr = (char**)malloc(sizeof(char *) * num_files + 1);
  if (ptr == NULL)
  {
    ft_putstr("Memory allocation failed");
    ft_exit("Oh No! The allocation failed!");
  }
  return (ptr);
}

void              ft_ptrfill(t_main *m)
{
  int             j;
  size_t          l;
  struct dirent   *dptr;

  j = 0;
  while ((dptr = readdir(m->dp)) != NULL) {
    l = ft_strlen(dptr->d_name) + 1;
    if (m->f.a == TRUE && dptr->d_name[0] == '.')
    {
      m->ptr[j] = ft_strndup(dptr->d_name, l);
      j++;
    }
    if (dptr->d_name[0] != '.')
    {
      m->ptr[j] = ft_strndup(dptr->d_name, l);
      j++;
    }
  }
  m->ptr[j] = NULL;
}
