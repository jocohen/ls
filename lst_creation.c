/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:45:26 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/20 15:22:32 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		get_type(mode_t st_mode)
{
	int		out;

	out = 0;
	(S_IFIFO == (S_IFMT & st_mode)) ? out = 1 : 1;
	(S_IFCHR == (S_IFMT & st_mode)) ? out = 2 : 1;
	(S_IFDIR == (S_IFMT & st_mode)) ? out = 3 : 1;
	(S_IFBLK == (S_IFMT & st_mode)) ? out = 4 : 1;
	(S_IFREG == (S_IFMT & st_mode)) ? out = 5 : 1;
	(S_IFLNK == (S_IFMT & st_mode)) ? out = 6 : 1;
	(S_IFSOCK == (S_IFMT & st_mode)) ? out = 7 : 1;
	(S_IFWHT == (S_IFMT & st_mode)) ? out = 8 : 1;
	return (out);
}

int		put_info(t_file **tmp, t_stat info, t_opt *opt)
{
	(*tmp)->perm = info.st_mode;
	(*tmp)->mode = get_type((*tmp)->perm);
	(*tmp)->n_hlink = info.st_nlink;
	if ((get_uid(tmp, info.st_uid, info.st_gid)) == -1)
	{
		return (ft_error(((*tmp)->user_del) ? (void **)&((*tmp)->uid) : 0,
	((*tmp)->grp_del) ? (void **)&((*tmp)->gid) : 0, (void **)tmp, 0));
	}
	(*tmp)->size = info.st_size;
	if (!opt->u)
		(*tmp)->m_time = info.st_mtime;
	else
		(*tmp)->m_time = info.st_atime;
	(*tmp)->maj = 0;
	(*tmp)->min = 0;
	if ((*tmp)->mode == 2 || (*tmp)->mode == 4)
	{
		(*tmp)->maj = major(info.st_rdev);
		(*tmp)->min = minor(info.st_rdev);
	}
	return (1);
}

int		new_elem(char *file, char *file_path, t_opt *opt, t_file **tmp)
{
	t_stat	info;

	if (!file_path)
		return (0);
	if (!(*tmp = (t_file *)malloc(sizeof(t_file))))
		return (0);
	ft_strcpy((*tmp)->file_id, file);
	if ((lstat(file_path, &info)) == -1)
	{
		write(2, "ls: ", 4);
		write(2, file_path, ft_strlen(file_path));
		write(2, ": ", 2);
		perror(0);
		(file_path) ? ft_memdel((void **)&file_path) : 0;
		ft_memdel((void **)tmp);
		return (1);
	}
	opt->blocks += info.st_blocks;
	if (!(put_info(tmp, info, opt)))
		return (0);
	(*tmp)->next = 0;
	ft_memdel((void **)&file_path);
	return (1);
}

int		lst_alloc(char **path, DIR *dir, t_file **first, t_opt *opt)
{
	t_dirent	*tmp;
	t_file		*traveler;

	traveler = 0;
	while (!traveler)
	{
		if (!(tmp = readdir(dir)))
			return (1);
		if (opt->f || opt->a || tmp->d_name[0] != '.')
		{
			if (!(new_elem(tmp->d_name, get_right_path(*path, tmp->d_name),
				opt, &traveler)))
				return (0);
			(*first) = traveler;
		}
	}
	while ((tmp = readdir(dir)))
		if (opt->f || opt->a || tmp->d_name[0] != '.')
		{
			if (!(new_elem(tmp->d_name, get_right_path(*path, tmp->d_name),
				opt, &traveler->next)))
				return (0);
			(traveler->next) ? traveler = traveler->next : 0;
		}
	return (1);
}

int		lst_creation(char **path, DIR *dir, t_file **first, t_opt *opt)
{
	(*first) = 0;
	if ((*path)[0] == '.' && (*path)[1] == 0)
		*path = 0;
	if (!(lst_alloc(path, dir, first, opt)))
		return (0);
	if (!(*path))
		(*path) = ".";
	if (!opt->f)
		travelsorter(first, opt);
	return (1);
}
