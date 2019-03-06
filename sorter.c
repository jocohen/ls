/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 11:54:02 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/16 12:55:51 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

/*
 ** lst : 0 current 1 lessH 2 lessT 3 equH 4 equT 5 largH 6 largT
*/

void	qsort_rtime(t_file **first, t_file **last)
{
	long int	pivot;
	t_file		*lst[7];

	if (!(*first))
		return ;
	intialize_lst_sort(lst, *first);
	pivot = (lst[0])->m_time;
	add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	while ((lst[0]))
	{
		if ((lst[0])->m_time < pivot)
			add_end(&(lst[0]), &(lst[1]), &(lst[2]));
		else if ((lst[0])->m_time > pivot)
			add_end(&(lst[0]), &(lst[5]), &(lst[6]));
		else
			add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	}
	qsort_rtime(&(lst[1]), &(lst[2]));
	qsort_rtime(&(lst[5]), &(lst[6]));
	end_the_sort(lst, first, last);
}

void	qsort_time(t_file **first, t_file **last)
{
	long int	pivot;
	t_file		*lst[7];

	if (!(*first))
		return ;
	intialize_lst_sort(lst, *first);
	pivot = (lst[0])->m_time;
	add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	while ((lst[0]))
	{
		if ((lst[0])->m_time > pivot)
			add_end(&(lst[0]), &(lst[1]), &(lst[2]));
		else if ((lst[0])->m_time < pivot)
			add_end(&(lst[0]), &(lst[5]), &(lst[6]));
		else
			add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	}
	qsort_time(&(lst[1]), &(lst[2]));
	qsort_time(&(lst[5]), &(lst[6]));
	end_the_sort(lst, first, last);
}

void	qsort_rev(t_file **first, t_file **last)
{
	int		result;
	char	*pivot;
	t_file	*lst[7];

	if (!(*first))
		return ;
	intialize_lst_sort(lst, *first);
	pivot = (lst[0])->file_id;
	add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	while ((lst[0]))
	{
		result = ft_strcmp(pivot, (lst[0])->file_id);
		if (result < 0)
			add_end(&(lst[0]), &(lst[1]), &(lst[2]));
		else if (result > 0)
			add_end(&(lst[0]), &(lst[5]), &(lst[6]));
		else
			add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	}
	qsort_rev(&(lst[1]), &(lst[2]));
	qsort_rev(&(lst[5]), &(lst[6]));
	end_the_sort(lst, first, last);
}

void	qsort_ascii(t_file **first, t_file **last)
{
	int		result;
	char	*pivot;
	t_file	*lst[7];

	if (!(*first))
		return ;
	intialize_lst_sort(lst, *first);
	pivot = (lst[0])->file_id;
	add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	while ((lst[0]))
	{
		result = ft_strcmp(pivot, (lst[0])->file_id);
		if (result > 0)
			add_end(&(lst[0]), &(lst[1]), &(lst[2]));
		else if (result < 0)
			add_end(&(lst[0]), &(lst[5]), &(lst[6]));
		else
			add_end(&(lst[0]), &(lst[3]), &(lst[4]));
	}
	qsort_ascii(&(lst[1]), &(lst[2]));
	qsort_ascii(&(lst[5]), &(lst[6]));
	end_the_sort(lst, first, last);
}

void	travelsorter(t_file **first, t_opt *opt)
{
	t_file	*tmp;

	tmp = (*first);
	while (tmp)
	{
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	if (opt->r)
		qsort_rev(first, &tmp);
	else
		qsort_ascii(first, &tmp);
	if (opt->t && opt->r)
		qsort_rtime(first, &tmp);
	else if (opt->t)
		qsort_time(first, &tmp);
	return ;
}
