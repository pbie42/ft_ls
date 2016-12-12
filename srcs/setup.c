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

int             ft_num_files(DIR *dp)
{
  struct dirent   *dptr;
  int             num_files;

  num_files = 0;
  while ((dptr = readdir(dp)) != NULL)
  {
    //Do not count the files beginning with '.'
    //TODO: will need to change this later on to include all files
    if (dptr->d_name[0] != '.')
      num_files++;
  }
  return (num_files);
}

long          ft_ptr_malloc(int num_files)
{
  long        *ptr;

  //Allocate memory to hold the addresses of the names of contents in current
  //working directory
  ptr = malloc(num_files*8);
  if (ptr == NULL) {
    ft_putstr("Memory allocation failed");
    ft_exit("Oh No! The allocation failed!");
  } else {
    //Initialize the memory by zeros
    memset(m->ptr, 0, m->num_files*8);
  }
}
