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
//we encounter, we display it's name. Now we can color the file based on whether
//it is an executable or a directory. We have also gotten rid of showing files
//that begin with a period as a typical ls command without any options does
//not show them.

int               main(int ac, char **av)
{
  struct dirent   *dptr;
  unsigned int    count;
  t_main          m;

  count = 0;
  m.curr_dir = getenv("PWD");
  //This function below will get the width of the terminal
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &m.w);
  if (ac > 1) {
    m.option = av[1];
  }
  //Get the value of environment variable PWD
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
    //Check if the name of the file/folder begins with '.'
    //if yes then we don't display it
    if (dptr->d_name[0] != '.') {
      //Check if the file is executable
      //The access function checks to see whether the file named by filename
      //(or in this case dptr->d_name) can be accessed in the way specfied by
      //the how argument. The how can be bitwise OR with the flags R_OK, W_OK,
      //X_OK, or the existence test F_OK. X_OK tests for execute/search
      //permission.
      if (!access(dptr->d_name, X_OK)) {
        int fd = -1;
        struct stat st;
        fd = open(dptr->d_name, O_RDONLY, 0);
        if (fd == -1) {
          ft_putstr("Failed to open File/Directory");
          return(-1);
        }
        fstat(fd, &st);
        //Check if it actually was a directory with execute permissions on it
        if (S_ISDIR(st.st_mode)) {
          //It it was a directory print blue
          ft_putstr(CYAN);
        	ft_putstr(dptr->d_name);
        	ft_putstr(STOP);
          ft_putstr("      ");
        } else {
          //If it was a normal executable print green
          ft_putstr(RED);
        	ft_putstr(dptr->d_name);
        	ft_putstr(STOP);
          ft_putstr("      ");
        }
        close(fd);
      } else {
        //ft_putstr("only going here");
        //No executable flag ON
        //Print it as default
        ft_putstr(dptr->d_name);
        ft_putstr("      ");
      }
    }
    //ft_putchar('\n');
    count++;
  }
  return(0);

}

//Will need to display the results in alphabetical order and then display them
//in a better format.
