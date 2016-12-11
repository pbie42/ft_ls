/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:16:01 by pbie              #+#    #+#             */
/*   Updated: 2016/05/19 15:09:41 by pbie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//In this first version of the LS we get the current working directory
//through the environment variable PWD. When we have the PWD we open it and
//iterate through it's contents by reading the directory. Each file or folder
//we encounter, we then display it's name.

int               main(void)
{
  char            *curr_dir;
  DIR             *dp;
  struct dirent   *dptr;
  unsigned int    count;

  curr_dir = NULL;
  dp = NULL;
  dptr = NULL;
  count = 0;
  //Get the value of environment variable PWD
  curr_dir = getenv("PWD");
  if (curr_dir == NULL)
  {
    ft_putstr("Error: Could not get the working directory");
    ft_putchar('\n');
    return(-1);
  }
  //Open the current directory
  dp = opendir((const char*)curr_dir);
  if (dp == NULL) {
    ft_putstr("Error: Could not open the working directory");
    ft_putchar('\n');
    return(-1);
  }
  ft_putchar('\n');
  //Go through and display all the names (files or folders)
  //contained in the directory.
  while ((dptr = readdir(dp)) != NULL) {
    ft_putstr(dptr->d_name);
    ft_putstr("     ");
    //ft_putchar('\n');
    count++;
  }
  return(0);

}

//As of right now this LS will show all files in the directory even those who
//begin with a period. The standard LS does not show any files starting with a
//period unless -a is included in the command line. My LS also does not color
//code the files, executables, directories, etc. Also as of right now the
//output is not in alphabetical order.
