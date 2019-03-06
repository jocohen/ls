/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapping_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:29:20 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/06 15:31:12 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		first_swap(t_file **tmp, t_file **aft, t_file **prev, t_file **first)
{
	(*prev)->next = (*aft);
	(*tmp)->next = (*prev);
	(*first) = (*tmp);
	(*prev) = (*first);
	(*tmp) = (*prev)->next;
	return (1);
}

int		swapping_3(t_file **tmp, t_file **aft, t_file **prev)
{
	(*tmp)->next = (*aft)->next;
	(*aft)->next = (*tmp);
	(*prev)->next = (*aft);
	(*tmp) = (*prev)->next;
	(*aft) = (*tmp)->next;
	return (1);
}
