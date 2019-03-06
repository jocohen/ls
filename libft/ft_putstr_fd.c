/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:14:55 by jocohen           #+#    #+#             */
/*   Updated: 2018/01/14 17:35:19 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	unsigned int	x;

	if (!s)
		return ;
	x = 0;
	while (s[x])
	{
		ft_putchar_fd(s[x], fd);
		x += 1;
	}
}
