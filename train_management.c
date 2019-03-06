/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   train_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:57:07 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/20 15:21:44 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	check_lnk(t_in_args *files, int y, t_opt *opt)
{
	t_stat	buf;

	if ((stat(files[y].name, &buf)) == -1)
		files[y].type = 3;
	else if (files[y].type != -1)
	{
		((S_IFDIR == (S_IFMT & buf.st_mode)) && !opt->l) ?
			files[y].type = 1 : 0;
		(files[y].type != 1) ? files[y].type = 3 : 1;
	}
	if (files[y].type == -1)
	{
		(S_IFDIR != (S_IFMT & buf.st_mode)) ? files[y].type = 3 : 1;
		(opt->l) ? files[y].type = 3 : 1;
	}
}

int		printf_bad_file(t_in_args *files, t_opt *opt)
{
	int		x;

	x = 0;
	if (!opt->f)
		bubble(files);
	while (files[x].name)
	{
		if (files[x].type == -2)
		{
			write(2, "ls: ", 4);
			write(2, files[x].name, ft_strlen(files[x].name));
			write(2, ": ", 2);
			perror(0);
		}
		x += 1;
	}
	return (1);
}

int		check_file(t_in_args *files, int y, t_opt *opt)
{
	t_stat	buf;
	int		x;

	x = 1;
	while (files[++y].name)
	{
		if ((lstat(files[y].name, &buf)) == -1)
		{
			files[y].type = -2;
			x = 2;
		}
		else if (S_IFLNK == (S_IFMT & buf.st_mode))
			check_lnk(files, y, opt);
		else if (files[y].type != -1 || (S_IFDIR != (S_IFMT & buf.st_mode)))
		{
			(S_IFDIR == (S_IFMT & buf.st_mode)) ? files[y].type = 1 : 0;
			(files[y].type != 1) ? files[y].type = 3 : 1;
		}
		(files[y].time != -2 && !opt->u) ? files[y].time = buf.st_mtime : 0;
		(files[y].time != -2 && opt->u) ? files[y].time = buf.st_atime : 0;
		(opt->d) ? files[y].type = 3 : 0;
	}
	return (x);
}

int		railway_distrib(t_in_args *files, t_opt *opt, int x)
{
	int		y;

	y = -1;
	while (files[++y].name)
		if (files[y].type == 3)
		{
			x = 0;
			if (!(lonely_railman(files, opt, 0, y)))
				return (0);
			break ;
		}
	y = -1;
	while (files[++y].name)
		if (files[y].type == 1 || files[y].type == -1)
		{
			(files[y].type == -1) ? x = 0 : 1;
			if (!(train_start(files[y].name, opt, ((x == -1) ?
								files[y].type = 2 : files[y].type))))
				return (0);
			(x == -1) ? x = 0 : 1;
		}
	return (1);
}

int		mult_input_deal(int ac, char **av, size_t x, t_opt *opt)
{
	t_in_args	files[ac];
	size_t		y;
	size_t		n;

	n = x;
	y = 0;
	(opt->d && !av[x]) ? files[y++].name = "." : 0;
	while (av[n])
	{
		files[y].name = av[n++];
		files[y].type = 0;
		files[y].time = 0;
		y += 1;
	}
	files[y].name = 0;
	if (!av[x] || !av[x + 1])
		files[y - 1].type = -1;
	if (!(n = check_file(files, -1, opt)))
		return (0);
	if (n == 2)
		if (!(printf_bad_file(files, opt)))
			return (0);
	if (av[x + 1] && !opt->f)
		railway_sort(files, opt);
	return (railway_distrib(files, opt, -1));
}
