/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_qsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 12:11:48 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/16 13:11:56 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	intialize_lst_sort(t_file **lst, t_file *first)
{
	lst[0] = first;
	lst[1] = 0;
	lst[2] = 0;
	lst[3] = 0;
	lst[4] = 0;
	lst[5] = 0;
	lst[6] = 0;
}

void	integrate(t_file **head1, t_file **tail1, t_file **head2,
			t_file **tail2)
{
	if (!(*tail2))
		(*tail2) = (*tail1);
	if (!(*head1))
		(*head1) = (*head2);
	else if ((*tail1))
		(*tail1)->next = (*head2);
}

void	add_end(t_file **tmp, t_file **head, t_file **tail)
{
	t_file	*t;

	t = (*tmp)->next;
	if (!(*head))
	{
		*head = *tmp;
		*tail = *tmp;
	}
	else
	{
		(*tail)->next = *tmp;
		(*tail) = (*tail)->next;
	}
	(*tmp)->next = 0;
	(*tmp) = t;
}

void	end_the_sort(t_file **lst, t_file **first, t_file **last)
{
	integrate(&(lst[1]), &(lst[2]), &(lst[3]), &(lst[4]));
	integrate(&(lst[1]), &(lst[4]), &(lst[5]), &(lst[6]));
	(*first) = (lst[1]);
	(*last) = (lst[6]);
}
