/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:27:39 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/16 14:52:49 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		normal_display(t_file *tmp, int x)
{
	while (tmp)
	{
		(tmp->mode == 3) ? x += 1 : 1;
		write(1, tmp->file_id, ft_strlen(tmp->file_id));
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (x);
}

int		display_all(t_file *tmp, t_opt *opt, const char *path, int type)
{
	int		x;

	x = 0;
	if (opt->br == 2 || type == 1 || type == 2)
	{
		(type != 2) ? write(1, "\n", 1) : 1;
		write(1, path, ft_strlen(path));
		write(1, ":\n", 2);
	}
	if ((opt->l || opt->g) && tmp && type)
	{
		write(1, "total ", 6);
		ft_putnbr(opt->blocks);
		write(1, "\n", 1);
	}
	if (opt->l || opt->g)
	{
		if ((x = formatting_vhs(tmp, path, opt->g, 0)) == -1)
			return (-1);
	}
	else
		x = normal_display(tmp, x);
	opt->blocks = 0;
	return (x);
}
