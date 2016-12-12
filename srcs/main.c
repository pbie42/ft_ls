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
//not show them. This version now shows the information as if we have done an
//ls -l. Will need to add options to choose between how I want things shown.
//NOTE: I have been taking pieces from the previous ft_ls I tried to make
//6 months ago.

int               ft_pwd(t_main *m)
{
  //Get the value of environment variable PWD
  m->curr_dir = getenv("PWD");
  //Check to make sure the current directory isn't null
  if (ft_pwdcheck(m->curr_dir))
    return (-1);
  //Open the current directory
  m->dp = opendir((const char*)m->curr_dir);
  if (ft_dircheck(m->dp))
    return (-1);
  m->num_files = ft_num_files(m->dp);
  //We are counting the number of files/folders inside the current working
  //directory. When it's done we close the directory.
  closedir(m->dp);
  return(0);
}

int               ft_num_file_check(t_main *m)
{
  //We then check that we should have at least one file/folder inside the
  //current working directory
  if (!m->num_files) {
    return(-1);
  } else {
    //Allocate memory to hold the addresses of the names of contents in current
    //working directory
    m->ptr = malloc(m->num_files*8);
    if (m->ptr == NULL) {
      ft_putstr("Memory allocation failed");
      return(-1);
    } else {
      //Initialize the memory by zeros
      memset(m->ptr, 0, m->num_files*8);
    }
  }

  //Now we open the directory again

  m->dp = opendir((const char*)m->curr_dir);
  if (ft_dircheck(m->dp))
    return (-1);
  return(0);
}

int               main(int ac, char **av)
{
  struct dirent   *dptr;
  int             count;
  int             j;
  int             k;
  t_main          m;

  count = 0;
  //This function below will get the width of the terminal
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &m.w);
  if (ac > 1) {
    m.option = av[1];
  }
  //Add variable to hold number of files inside the directory
  m.num_files = 0;

  if (ft_pwd(&m) == -1)
    return(-1);


  //We restore the values back to NULL since we will use them again later

  m.dp = NULL;
  dptr = NULL;

  if (ft_num_file_check(&m) == -1)
    return(-1);


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
    int fd = -1;
    struct stat st;

    fd = open((char*)m.ptr[count], O_RDONLY, 0);
    if (fd == -1) {
      ft_putstr("Failed to open file/directory");
      ft_putchar('\n');
      free(m.ptr);
      return(-1);
    }
    //Call fstat to get the stat info about the file
    if (fstat(fd, &st)) {
      ft_putstr("Fstat Failed");
      close(fd);
      free(m.ptr);
      return(-1);
    }
    //Check if the file is a directory
    if (S_ISDIR(st.st_mode)) {
      ft_putchar('d');
    } else {
      ft_putchar('-');
    }
    //Check the owner permission
    mode_t permission = st.st_mode & S_IRWXU;
    if (permission & S_IRUSR) {
      ft_putchar('r');
    } else {
      ft_putchar('-');
    }
    if (permission & S_IWUSR) {
      ft_putchar('w');
    } else {
      ft_putchar('-');
    }
    if (permission & S_IXUSR) {
      ft_putchar('x');
    } else {
      ft_putchar('-');
    }
    //Check the group permission
    permission = st.st_mode & S_IRWXG;
    if (permission & S_IRGRP) {
      ft_putchar('r');
    } else {
      ft_putchar('-');
    }
    if (permission & S_IWGRP) {
      ft_putchar('w');
    } else {
      ft_putchar('-');
    }
    if (permission & S_IXGRP) {
      ft_putchar('x');
    } else {
      ft_putchar('-');
    }
    //Check other's permission
    permission = st.st_mode & S_IRWXO;
    if (permission & S_IROTH) {
      ft_putchar('r');
    } else {
      ft_putchar('-');
    }
    if (permission & S_IWOTH) {
      ft_putchar('w');
    } else {
      ft_putchar('-');
    }
    if (permission & S_IXOTH) {
      ft_putchar('x');
    } else {
      ft_putchar('-');
    }

    //Print the number of hard links
    ft_putnbr((int)st.st_nlink);

    //Get the user name
    struct passwd *pt = getpwuid(st.st_uid);
    ft_putstr(pt->pw_name);

    //Get the group name
    struct group *p = getgrgid(st.st_gid);
    ft_putstr(p->gr_name);

    //Get the file size
    ft_putnbr((long long)st.st_size);

    //Get the date and time. We will have to remove the trailing newline.
    char date_time[100];
    ft_memset(date_time, 0, sizeof(date_time));
    ft_strncpy(date_time, ctime(&st.st_ctime), sizeof(date_time));
    int c = 0;
    while (date_time[c] != '\0') {
      if (date_time[c] == '\n') {
        date_time[c] = '\0';
      }
      c++;
    }
    ft_putstr(date_time);

    //Check if the file/folder is executable.
    if (!access((const char*)m.ptr[count], X_OK)) {
      if (S_ISDIR(st.st_mode)) {
        //If folder print in blue
        ft_foldercolor(m.ptr, count);
      } else {
        //If executable print in magenta
        ft_execcolor(m.ptr, count);
      }
    } else {
      //If normal print as default
      ft_putendl((char*)m.ptr[count]);
    }
    count++;
  }
  //Free the allocated memory
  free(m.ptr);
  return(0);

}
