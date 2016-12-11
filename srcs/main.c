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

int               main(int ac, char **av)
{
  struct dirent   *dptr;
  unsigned int    count;
  t_main          m;

  count = 0;
  if (ac > 1)
    m.option = av[1];
  //Get the value of environment variable PWD
  m.curr_dir = getenv("PWD");
  if (m.curr_dir == NULL)
  {
    ft_putstr("Error: Could not get the working directory");
    ft_putchar('\n');
    return(-1);
  }
  //Open the current directory
  m.dp = opendir((const char*)m.curr_dir);
  if (m.dp == NULL) {
    ft_putstr("Error: Could not open the working directory");
    ft_putchar('\n');
    return(-1);
  }
  ft_putchar('\n');
  //Go through and display all the names (files or folders)
  //contained in the directory.
  while ((dptr = readdir(m.dp)) != NULL) {
    //Check if an option has been given to our ft_ls. If it has
    //an option then display everything. This will eventually be the
    //response for -a
    if (m.option) {
      ft_putstr(dptr->d_name);
      ft_putstr("     ");
    } else {
      //Check if the name of the file/folder begins with '.'
      //if yes then we don't display it
      if (dptr->d_name[0] != '.') {
        ft_putstr(dptr->d_name);
        ft_putstr("     ");
      }
    }
    //ft_putchar('\n');
    count++;
  }
  return(0);

}

//Now my ft_ls will take options but the options do not do anything at the
//moment other than make the ft_ls display all of the files and folders
//even if they start with a period. If no option is given then only files and
//folders that do NOT start with a period will be shown. 
