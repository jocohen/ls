/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 17:50:15 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/14 18:56:15 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	initialize(t_opt *opt)
{
	opt->r = 0;
	opt->br = 0;
	opt->t = 0;
	opt->l = 0;
	opt->a = 0;
	opt->f = 0;
	opt->t = 0;
	opt->u = 0;
	opt->g = 0;
	opt->d = 0;
	opt->blocks = 0;
}

int		usage(char c)
{
	write(1, "ls: illegal option -- ", 22);
	write(1, &c, 1);
	write(1, "\nusage: ls [-Radfglrtu] [file ...]\n", 35);
	return (0);
}

int		check_opt(char a, t_opt *opt)
{
	if (a == 'r')
		opt->r = 1;
	else if (a == 'l')
		opt->l = 1;
	else if (a == 'a')
		opt->a = 1;
	else if (a == 'f')
		opt->f = 1;
	else if (a == '1' || !a)
		return (1);
	else if (a == 'R')
		opt->br = 1;
	else if (a == 't')
		opt->t = 1;
	else if (a == 'u')
		opt->u = 1;
	else if (a == 'g')
		opt->g = 1;
	else if (a == 'd')
		opt->d = 1;
	else
		return (usage(a));
	return (1);
}

int		get_options(char **av, t_opt *opt)
{
	size_t	x;
	size_t	y;

	y = 1;
	initialize(opt);
	if (!av[1] || av[1][0] != '-' || !av[1][1])
		return (1);
	while (av[y] && av[y][0] == '-')
	{
		x = 1;
		if (!av[y][x])
			return (y);
		while (av[y][x])
		{
			if (!(check_opt(av[y][x], opt)))
				return (0);
			x += 1;
		}
		y += 1;
	}
	return (y);
}
