/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:22:13 by jocohen           #+#    #+#             */
/*   Updated: 2018/05/31 11:05:04 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		main(int ac, char **av)
{
	t_opt		opt;
	size_t		x;

	(void)ac;
	if (!(x = get_options(av, &opt)))
		return (1);
	if (!av[x] && !opt.d)
	{
		if (!(train_start(av[x], &opt, -1)))
			return (1);
	}
	else
	{
		(x > 1) ? ac -= x : 1;
		(!av[x]) ? ac += 1 : 0;
		if (!(mult_input_deal(ac, av, x, &opt)))
			return (1);
	}
	return (0);
}
