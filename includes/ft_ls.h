/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:35:08 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/17 20:13:42 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# ifndef _DARWIN_FEATURE_64_BIT_INODE
#  define N_L 256
# endif

# ifdef _DARWIN_FEATURE_64_BIT_INODE
#  define N_L 1024
# endif
# define MAX_FORMAT 71

# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <sys/stat.h>
# include <limits.h>
# include <time.h>
# include <errno.h>
# include "../libft/includes/libft.h"

typedef struct dirent	t_dirent;

typedef struct stat		t_stat;

typedef struct timespec	t_timespec;

typedef struct			s_padd
{
	int					link;
	int					usr;
	int					grp;
	int					size;
	int					maj;
	int					min;
}						t_padd;

typedef struct			s_in_args
{
	char				*name;
	int					type;
	long int			time;
}						t_in_args;

typedef struct			s_opt
{
	int					l;
	int					a;
	int					br;
	int					r;
	int					t;
	int					u;
	int					f;
	int					g;
	int					d;
	long long			blocks;
}						t_opt;

typedef struct			s_file
{
	char				file_id[N_L];
	int					mode;
	mode_t				perm;
	nlink_t				n_hlink;
	int					user_del;
	int					grp_del;
	char				*gid;
	char				*uid;
	off_t				size;
	long int			m_time;
	int					maj;
	int					min;
	struct s_file		*next;
}						t_file;

int						mult_input_deal(int ac, char **av,
							size_t x, t_opt *opt);
int						train_start(const char *path, t_opt *opt, int type);
int						lonely_railman(t_in_args *files, t_opt *opt,
							t_file *first, int y);

int						lst_creation(char **path, DIR *dir, t_file **first,
							t_opt *opt);
int						new_elem(char *file, char *file_path, t_opt *opt,
							t_file **tmp);
int						put_info(t_file **tmp, t_stat info, t_opt *opt);
int						del_all_lst(t_file **lst, int x);
int						ft_error(void **a1, void **a2, void **a3, void **a4);

void					travelsorter(t_file **first, t_opt *opt);
void					railway_sort(t_in_args *files, t_opt *opt);
void					bubble(t_in_args *files);
int						first_swap(t_file **tmp, t_file **aft, t_file **prev,
							t_file **first);
int						swapping_3(t_file **tmp, t_file **aft, t_file **prev);
int						regular_swap(t_in_args *files, size_t y);

void					intialize_lst_sort(t_file **lst, t_file *first);
void					integrate(t_file **head1, t_file **tail1,
							t_file **head2, t_file **tail2);
void					add_end(t_file **tmp, t_file **head, t_file **tail);
void					end_the_sort(t_file **lst, t_file **first,
							t_file **last);
void					qsort_ascii(t_file **first, t_file **last);

int						get_options(char **av, t_opt *opt);
char					*get_right_path(const char *path, char *file_name);
int						get_uid(t_file **tmp, uid_t st_uid, gid_t st_gid);

int						display_all(t_file *first, t_opt *opt,
							const char *path, int type);
int						formatting_vhs(t_file *tmp, const char *path,
							int g, int t);
void					set_format(t_file *tmp, char *format, t_padd p, int g);
int						normal_l_display(t_file *tmp, char *format,
							const char *path, int g);
int						link_display(t_file *tmp, char *path,
							char *format, int g);
int						block_chr_display(t_file *tmp, char *format,
							const char *path, int g);
char					*get_time(t_file *tmp);
void					get_rights(t_file *tmp, char rights[12],
							char *path_file);
int						n_digit(long n);
void					initialize_padd(t_padd *p, t_file *tmp, int *type);
void					put_type_format(t_file *tmp, char *format,
							t_padd padd, int *type);

#endif
