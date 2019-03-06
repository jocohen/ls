/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_railman.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:39:28 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/20 15:24:09 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		create_elem(t_file **tmp, char *path, t_opt *opt)
{
	t_stat	info;

	if (!(*tmp = (t_file *)malloc(sizeof(t_file))))
		return (0);
	ft_strcpy((*tmp)->file_id, path);
	if ((lstat(path, &info)) == -1)
	{
		ft_memdel((void **)tmp);
		write(2, "ls: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		perror(0);
		return (1);
	}
	if (!(put_info(tmp, info, opt)))
		return (0);
	(*tmp)->next = 0;
	return (1);
}

int		lonely_railman(t_in_args *files, t_opt *opt, t_file *first, int y)
{
	t_file	*tmp;

	while (!first && files[y].name)
	{
		if (!(create_elem(&first, files[y].name, opt)))
			return (0);
		if (first)
			tmp = first;
		else
			y += 1;
	}
	while (files[++y].name)
		if (files[y].type == 3)
		{
			if (!(create_elem(&tmp->next, files[y].name, opt)))
				return (0);
			(tmp->next) ? tmp = tmp->next : 0;
		}
	if ((display_all(first, opt, ".", 0)) == -1)
		return (del_all_lst(&first, 0));
	del_all_lst(&first, 0);
	return (1);
}
