/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   railway_sorting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 19:32:00 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/10 19:52:42 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	bubble_r(t_in_args *files)
{
	size_t	y;
	int		x;

	x = 1;
	while (x)
	{
		x = 0;
		y = 0;
		while (files[y + 1].name)
		{
			if (ft_strcmp(files[y].name, files[y + 1].name) < 0)
				x += regular_swap(files, y);
			y += 1;
		}
	}
}

void	bubble_rtime(t_in_args *files)
{
	size_t	y;
	int		x;

	x = 1;
	while (x)
	{
		x = 0;
		y = 0;
		while (files[y + 1].name)
		{
			if (files[y].time > files[y + 1].time)
				x += regular_swap(files, y);
			else if (files[y].time == files[y + 1].time)
				if (ft_strcmp(files[y].name, files[y + 1].name) < 0)
					x += regular_swap(files, y);
			y += 1;
		}
	}
}

void	bubble_time(t_in_args *files)
{
	size_t	y;
	int		x;

	x = 1;
	while (x)
	{
		x = 0;
		y = 0;
		while (files[y + 1].name)
		{
			if (files[y].time < files[y + 1].time)
				x += regular_swap(files, y);
			else if (files[y].time == files[y + 1].time)
				if (ft_strcmp(files[y].name, files[y + 1].name) > 0)
					x += regular_swap(files, y);
			y += 1;
		}
	}
}

void	bubble(t_in_args *files)
{
	size_t	y;
	int		x;

	x = 1;
	while (x)
	{
		x = 0;
		y = 0;
		while (files[y + 1].name)
		{
			if (ft_strcmp(files[y].name, files[y + 1].name) > 0)
				x += regular_swap(files, y);
			y += 1;
		}
	}
}

void	railway_sort(t_in_args *files, t_opt *opt)
{
	if (opt->r == 1 && opt->t == 0)
		bubble_r(files);
	else if (opt->r == 1 && opt->t == 1)
		bubble_rtime(files);
	else if (opt->t == 1)
		bubble_time(files);
	else
		bubble(files);
	return ;
}
