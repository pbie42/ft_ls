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

//Have begun the process of taking options and finding the ones I can use.
//TODO will need to start the recursion process before using any flags.

int								ft_pwd(t_main *m)
{
	//Get the string value of the Present Working Directory
	m->curr_dir = getenv("PWD");
	//Check to make sure the current directory isn't null
	if (ft_pwdcheck(m->curr_dir))
		return (-1);
	//Open the current directory
	m->ds = opendir((const char*)m->curr_dir);
	if (ft_dircheck(m->ds))
		return (-1);
	// We pass the directory stream and the flags struct in our main struct to
	// num files to get the number of files with regards to our flags
	m->num_files = ft_num_files(m->ds, m->f);
	//We are counting the number of files/folders inside the current working
	//directory. When it's done we close the directory stream.
	closedir(m->ds);
	return (0);
}

int								ft_num_file_check(t_main *m)
{
	//We then check that we should have at least one file/folder inside the
	//current working directory
	if (!m->num_files)
		return (-1);
	else
		m->ptr = ft_ptr_malloc(m->num_files);

	//Now we open the directory again

	m->ds = opendir((const char*)m->curr_dir);
	if (ft_dircheck(m->ds))
		return (-1);
	return (0);
}

void									ft_something(char *pwd, t_flags f)
{
	t_files							*files;
	t_files							*head;
	char								*newPWD;

	// ft_putendl("entering ft_something");
	files = ft_list(pwd, f);
	// ft_putendl("exiting ft_list in ft_something");
	head = files;
	// ft_putendl("getting here homie?");
	while (files->next)
	{
		// ft_putendl("entering printR");
		ft_printR(files, f);
		// ft_putendl("exiting printR");
		files = files->next;
	}
	// ft_putendl("left ft_something first while");
	ft_printR(files, f);
	while (head->next)
	{
		if (!access((const char*)(head)->dptr->d_name, X_OK))
		{
			if (S_ISDIR((head)->st_mode))
			{
				if (ft_strcmp((head)->dptr->d_name, ".")
					&& ft_strcmp((head)->dptr->d_name, ".."))
				{
					ft_putchar('\n');
					// ft_putendl("entering make path");
					newPWD = make_path_fl(pwd, (head)->name);
					// ft_putendl("exited make path");
					ft_putendl(newPWD);
					ft_something(newPWD, f);
				}
			}
		}
		head = head->next;
	}
}

int									main(int ac, char **av)
{
	struct dirent					*dptr;
	t_main							m;
	char								*pwd;

	m.num_files = 0;
	dptr = NULL;
	// files = NULL;
	if (ac > 1 && av[1][0] == '-')
		ft_find_flags(av, &m.f);
	// // ioctl(STDOUT_FILENO, TIOCGWINSZ, &m.w); // This should be returning into something
	if (m.f.lg_r == FALSE)
	{
		if (ft_pwd(&m) == -1)
			return (-1);
		if (ft_num_file_check(&m) == -1)
			return (-1);
		ft_ptrfill(&m);
		ft_alphastrsort(&m);
		ft_print(m);
		// ft_putendl("going to large r");
	}
	pwd = getenv("PWD");
	if (m.f.lg_r == TRUE)
	{
		ft_something(pwd, m.f);
	}
	
	//Free the allocated memory
	// free(files);
	// free(m.ptr);
	return (0);
}
