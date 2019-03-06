/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padd_materializing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:25:17 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/12 13:14:28 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	set_zero(t_padd *p, int *type)
{
	(*type) = 0;
	p->link = 0;
	p->usr = 0;
	p->grp = 0;
	p->size = 0;
	p->maj = 0;
	p->min = 0;
}

void	blck_chr_padd(t_padd *p, t_file *tmp)
{
	int		x;

	x = n_digit(tmp->maj) + 1;
	(x > p->maj) ? p->maj = x : 1;
	x = n_digit(tmp->min) + 1;
	(x > p->min) ? p->min = x : 1;
	if (p->size > p->maj + p->min + 1)
		p->maj = (p->size - (p->min + 1));
	else if (p->maj + p->min + 1 > p->size)
		p->size = p->maj + p->min + 1;
}

void	initialize_padd(t_padd *p, t_file *tmp, int *type)
{
	int		x;

	x = 0;
	set_zero(p, type);
	while (tmp)
	{
		x = n_digit(tmp->n_hlink) + 1;
		(x > p->link) ? p->link = x : 1;
		x = ft_strlen(tmp->uid) + 2;
		(x > p->usr) ? p->usr = x : 1;
		x = ft_strlen(tmp->gid) + 2;
		(x > p->grp) ? p->grp = x : 1;
		if (tmp->mode != 2 && tmp->mode != 4)
		{
			x = n_digit(tmp->size);
			(x > p->size) ? p->size = x : 1;
		}
		else
			blck_chr_padd(p, tmp);
		tmp = tmp->next;
	}
}
