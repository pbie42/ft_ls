/*	**************************************************************************	*/
/*																																																																												*/
/*																																																								:::						::::::::			*/
/*			ft_ls.h																																												:+:						:+:				:+:			*/
/*																																																				+:+	+:+									+:+					*/
/*			By:	pbie	<marvin@42.fr>																								+#+		+:+							+#+								*/
/*																																																+#+#+#+#+#+			+#+											*/
/*			Created:	2016/12/11	13:17:17	by	pbie														#+#				#+#													*/
/*			Updated:	2016/12/11	15:16:26	by	pbie													###			########.fr							*/
/*																																																																												*/
/*	**************************************************************************	*/

#ifndef	FT_LS_H
#	define	FT_LS_H

#	define	TRUE	1
#	define	FALSE	0
#	define	STOP	"\033[0;0m"
#	define	EOC	"\033[39m"
#	define	EOBG	"\033[49m"
#	define	BOLD	"\033[1m"
#	define	UNDERLINE	"\033[1m"
#	define	BLACK	"\033[30m"
#	define	WHITE	"\033[97m"
#	define	BLUE	"\033[34m"
#	define	RED	"\033[31m"
#	define	GREEN	"\033[32m"
#	define	YELLOW	"\033[33m"
#	define	MAGENTA	"\033[35m"
#	define	CYAN	"\033[36m"
#	define	GRAY	"\033[37m"
#	define	BGBLACK	"\033[40m"
#	define	BGRED	"\033[41m"
#	define	BGGREEN	"\033[42m"
#	define	BGYELLOW	"\033[43m"
#	define	BGBLUE	"\033[44m"
#	define	BGMAGENTA	"\033[45m"
#	define	BGCYAN	"\033[46m"
#	define	BGLIGHT	"\033[47m"
#	define	BGGRAY	"\033[47m"

#	include	<stdio.h>
#	include	<string.h>
#	include	<stdlib.h>
#	include	<sys/types.h>
#	include	<dirent.h>
#	include	<sys/stat.h>
#	include	<unistd.h>
#	include	<fcntl.h>
#	include	<sys/ioctl.h>
#	include	<pwd.h>
#	include	<grp.h>
#	include	<time.h>
#	include	"../libft/includes/libft.h"

typedef	int						t_bool;

typedef	struct				s_files
{
		struct	s_files			*next;
		struct	s_files			*prev;
		struct	s_files			*sub_dir;
		time_t							mtime;
		mode_t							st_mode;
		nlink_t							st_nlink;
		uid_t								st_uid;
		gid_t								st_gid;
		off_t								st_size;
		ino_t								st_ino;
		blkcnt_t						st_blocks;
		struct	dirent				*dptr;
}											t_files;

typedef	struct								s_flags
{
		t_bool							l;
		t_bool							a;
		t_bool							t;
		t_bool							sm_r;
		t_bool							lg_r;
}																					t_flags;

typedef	struct								s_main
{
		char								*curr_dir;
		DIR									*dp;
		char								*option;
		struct		winsize					w;
		char								*ptr;
		int									num_files;
		int									filesize1;
		t_flags							flgs;
}																					t_main;

void									ft_foldercolor(char	**ptr,	int	count);
void									ft_execcolor(char	**ptr,	int	count);
void									ft_foldercolornorm(char	**ptr,	int	count);
void									ft_execcolornorm(char	**ptr,	int	count);
void									ft_normcolornorm(char	**ptr,	int	count);
void									ft_ptrfill(t_main	*m);
void									ft_init_flags(t_flags	*f);
void									ft_which_flags(char	*ops,	t_flags	*f);
void									ft_find_flags(char	**options,	t_flags	*f);
void									ft_alphastrsort(t_main	*m);
void									ft_print(t_main	m);
void									ft_printpermissions(struct	stat	st);
//void																		ft_list_push_back(t_files	**begin_list,	struct	dirent	*ent,	char	*path);
int										ft_pwdcheck(char	*curr_dir);
int										ft_dircheck(DIR	*dp);
int										ft_num_files(DIR	*dp,	t_flags	f);
char																		**ft_ptr_malloc(int	num_files);
//t_files															*ft_lstnew(struct	dirent	*ent,	char	*path);
char									*make_path_fl(char	*dir,	char	*file);









#endif
