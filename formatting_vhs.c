/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_vhs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:38:27 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/16 15:07:53 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		n_digit(long n)
{
	size_t	d;

	d = 1;
	while ((n / 10))
	{
		n = n / 10;
		d += 1;
	}
	return (d);
}

void	add_padd(char *format, int padd)
{
	int		d;
	int		num;
	int		x;
	int		keep_padd;

	keep_padd = padd;
	x = n_digit(padd);
	while (x)
	{
		padd = keep_padd;
		d = 1;
		while ((padd / 10) && d < x)
		{
			padd = padd / 10;
			d += 1;
		}
		num = padd % 10;
		ft_strcatc(format, (num + '0'));
		x -= 1;
	}
}

void	set_format(t_file *tmp, char *format, t_padd p, int g)
{
	ft_bzero(format, MAX_FORMAT);
	ft_strcat(format, "%s%");
	add_padd(format, p.link);
	ft_strcat(format, "d %-");
	if (!g)
	{
		add_padd(format, p.usr);
		ft_strcat(format, "s%-");
	}
	add_padd(format, p.grp);
	ft_strcat(format, "s%");
	if (tmp->mode == 2 || tmp->mode == 4)
	{
		add_padd(format, p.maj);
		ft_strcat(format, "d,%");
		add_padd(format, p.min);
		ft_strcat(format, "d%s%s\n");
	}
	else
	{
		add_padd(format, p.size);
		(tmp->mode == 6) ? ft_strcat(format, "lld%s%s -> %s\n") : 0;
		(tmp->mode != 6) ? ft_strcat(format, "lld%s%s\n") : 0;
	}
}

int		disp(t_file *tmp, char *format, const char *path, int g)
{
	if (tmp->mode == 6)
	{
		if (!(link_display(tmp, (char *)path, format, g)))
			return (-1);
	}
	else if (tmp->mode == 2 || tmp->mode == 4)
	{
		if (!(block_chr_display(tmp, format, path, g)))
			return (-1);
	}
	else
	{
		if (!(normal_l_display(tmp, format, path, g)))
			return (-1);
	}
	return (1);
}

int		formatting_vhs(t_file *tmp, const char *path, int g, int t)
{
	char		format[MAX_FORMAT];
	int			type;
	t_padd		padd;
	int			x;

	x = 0;
	initialize_padd(&padd, tmp, &type);
	while (tmp)
	{
		(tmp->mode == 3) ? x += 1 : 0;
		t = tmp->user_del;
		tmp->user_del = g;
		put_type_format(tmp, format, padd, &type);
		tmp->user_del = t;
		if (!(disp(tmp, format, path, g)))
			return (-1);
		tmp = tmp->next;
	}
	return (x);
}
