/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 13:29:49 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/31 15:56:58 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		del_all_lst(t_file **lst, int x)
{
	t_file	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		((*lst)->user_del) ? ft_memdel((void **)&((*lst)->uid)) : 1;
		((*lst)->grp_del) ? ft_memdel((void **)&((*lst)->gid)) : 1;
		ft_memdel((void **)lst);
		(*lst) = tmp;
	}
	return (x);
}

char	*get_right_path(const char *path, char *file_name)
{
	size_t	x;
	char	*str;
	size_t	y;

	x = 0;
	y = 0;
	(path) ? x += 1 : 1;
	if (!(str = ft_memalloc(ft_strlen(path) + ft_strlen(file_name) + x + 1)))
		return (0);
	x = 0;
	if (path)
	{
		while (path[x])
		{
			str[x] = path[x];
			x += 1;
		}
		(x && path[x - 1] != '/') ? str[x++] = '/' : 0;
	}
	while (file_name[y])
		str[x++] = file_name[y++];
	return (str);
}

int		tchoutchou(const char *path, t_opt *opt, t_file *first, int type)
{
	t_file	*tmp;
	char	*str;
	int		x;

	tmp = first;
	if ((x = display_all(tmp, opt, path, type)) == -1)
		return (0);
	while (x && tmp && opt->br >= 1)
	{
		if ((tmp->mode == 3) && ((tmp->file_id[0] != '.' ||
	tmp->file_id[1] != 0) && (tmp->file_id[1] != '.' || tmp->file_id[2] != 0)))
		{
			if (!(str = get_right_path(path, tmp->file_id)))
				return (0);
			opt->br = 2;
			if (!(train_start(str, opt, 1)))
				return (ft_error((void **)&str, 0, 0, 0));
			ft_memdel((void **)&str);
		}
		tmp = tmp->next;
	}
	del_all_lst(&first, 0);
	return (1);
}

int		waiting_for_railman(const char *str, DIR **dir, int type)
{
	if (!((*dir) = opendir(str)))
	{
		if (type == 1 || type == 2)
		{
			(type == 1) ? write(1, "\n", 1) : 1;
			write(1, str, ft_strlen(str));
			write(1, ":\n", 2);
		}
		write(2, "ls: ", 4);
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		perror(0);
		return (0);
	}
	return (1);
}

int		train_start(const char *path, t_opt *opt, int type)
{
	DIR			*dir;
	t_file		*first;

	first = 0;
	if (!path)
		path = ".";
	if (!(waiting_for_railman(path, &dir, type)))
		return (-1);
	if (!(lst_creation((char **)&path, dir, &first, opt)))
	{
		closedir(dir);
		return (del_all_lst(&first, -1));
	}
	if (!(tchoutchou(path, opt, first, type)))
	{
		closedir(dir);
		return (del_all_lst(&first, 0));
	}
	closedir(dir);
	return (1);
}
