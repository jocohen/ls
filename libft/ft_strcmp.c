/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:12:34 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:36:16 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	x;

	x = 0;
	while (s1[x] == s2[x] && s1[x] && s2[x])
		x += 1;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
