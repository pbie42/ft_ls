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
//iterate through it's contents by reading the directory. We then sort through
//each file or folder to put them in alphabetical order. Once we have
//alphabetized the folders we display them. The file colors are based on whether
//it is an executable or a directory. We have also gotten rid of showing files
//that begin with a period as a typical ls command without any options does
//not show them. Still need to diplay the output correctly on the screen.
//NOTE: I have been taking pieces from the previous ft_ls I tried to make
//6 months ago.

int               main(int ac, char **av)
{
  struct dirent   *dptr;
  int    count;
  int    j;
  int    k;
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
  //Add variable to hold number of files inside the directory
  m.num_files = 0;
  //Open the current directory
  m.dp = opendir((const char*)m.curr_dir);
  while ((dptr = readdir(m.dp)) != NULL) {
    //Do not count the files beginning with '.'
    if (dptr->d_name[0] != '.') {
      m.num_files++;
    }
  }
  //We are counting the number of files/folders inside the current working
  //directory. When it's done we close the directory.
  closedir(m.dp);

  //We restore the values back to NULL since we will use them again later

  m.dp = NULL;
  dptr = NULL;

  //We then check that we should have at least one file/folder inside the
  //current working directory

  if (!m.num_files) {
    return(0);
  } else {
    //Allocate memory to hold the addresses of the names of contents in current
    //working directory
    m.ptr = malloc(m.num_files*8);
    if (m.ptr == NULL) {
      ft_putstr("Memory allocation failed");
      return(-1);
    } else {
      //Initialize the memory by zeros
      memset(m.ptr, 0, m.num_files*8);
    }
  }

  //Now we open the directory again

  m.dp = opendir((const char*)m.curr_dir);

  if (m.dp == NULL) {
    ft_putstr("Error: Could not open the working directory");
    ft_putchar('\n');
    free(m.ptr);
    return(-1);
  }
  //ft_putchar('\n');
  //Start iterating the directory and read all its contents inside an array
  //that we allocated above.
  j = 0;
  while ((dptr = readdir(m.dp)) != NULL) {
    if (dptr->d_name[0] != '.') {
      m.ptr[j] = (long)dptr->d_name;
      j++;
    }
  }
  //Start sorting the names alphabetically using bubble sorting here
  while (count < m.num_files - 1) {
    k = count + 1;
    while (k < (m.num_files)) {
      char *c = (char*)m.ptr[count];
      char *d = (char*)m.ptr[k];
      //Check that the two characters should be from the same set
      if ( ((*c >= 'a') && (*d >= 'a')) || ((*c <= 'Z') && (*d <= 'Z')) ) {
        int i = 0;
        //If initial characters are the same, continue comparing the characters
        //until a difference is found.
        if (*c == *d) {
          while (*(c + i) == *(d + i)) {
            i++;
          }
        }
        //Check if the earlier stored value is alphabetically higher than the
        //next value
        if (*(c + i) > *(d + i)) {
          //If yes, then swap the values
          long temp = 0;
          temp = m.ptr[count];
          m.ptr[count] = m.ptr[j];
          m.ptr[j] = temp;
        }
      } else {
        //If the two beginning characters are not from the same ASCII set then
        //make them the same and then compare them
        int off_1 = 0;
        int off_2 = 0;
        if (*c <= 'Z') {
          off_1 = 32;
        }
        if (*d <= 'Z') {
          off_2 = 32;
        }
        int i = 0;
        //After the character set are made same, check if the begninning
        //characters are same. If yes, then continue searching until we find
        //some difference.
        if (*c + off_1 == *d + off_2) {
          while (*(c + off_1 + i) == *(d + off_2 + i)) {
            i++;
          }
        }
        //After difference is found, check if a swap is required.
        if ((*c + off_1 + i) > (*d + off_2 + i)) {
          //If yes we do the swap
          long temp = 0;
          temp = m.ptr[count];
          m.ptr[count] = m.ptr[j];
          m.ptr[j] = temp;
        }
      }
      k++;
    }
    count++;
  }

  //Now that the names are sorted alphabetically we need to display them
  //to the console
  count = 0;
  while (count < m.num_files) {
    //Check if the file/folder is executable
    if (!access((const char*)m.ptr[count], X_OK)) {
      int fd = -1;
      struct stat st;

      fd = open((char*)m.ptr[count], O_RDONLY, 0);
      if (fd == -1) {
        ft_putstr("Failed to open file/directory");
        ft_putchar('\n');
        free(m.ptr);
        return(-1);
      }
      fstat(fd, &st);
      if (S_ISDIR(st.st_mode)) {
        //If folder, print in blue
        ft_foldercolornorm(m.ptr, count);
      } else {
        //If executable print in green
        ft_execcolornorm(m.ptr, count);
      }
      close(fd);
    } else {
      //If normal file print by default
      ft_normcolornorm(m.ptr, count);
    }
    count++;
  }
  free(m.ptr);
  return(0);

}

//Will need to display the results in a proper format
