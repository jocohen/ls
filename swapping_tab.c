/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapping_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 19:37:10 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/10 19:38:29 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		regular_swap(t_in_args *files, size_t y)
{
	char		*tmp;
	long int	t;
	int			p;

	tmp = files[y].name;
	p = files[y].type;
	t = files[y].time;
	files[y].name = files[y + 1].name;
	files[y].type = files[y + 1].type;
	files[y].time = files[y + 1].time;
	files[y + 1].name = tmp;
	files[y + 1].type = p;
	files[y + 1].time = t;
	return (1);
}
