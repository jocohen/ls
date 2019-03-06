/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:34:53 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/13 14:24:31 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

int		get_gid(t_file **tmp, gid_t st_gid)
{
	struct group	*grp;

	errno = 0;
	if (!(grp = getgrgid(st_gid)))
	{
		if (errno)
			return (-1);
		if (!((*tmp)->gid = ft_itoa(st_gid)))
			return (-1);
		(*tmp)->grp_del = 1;
	}
	else
		(*tmp)->gid = grp->gr_name;
	return (1);
}

int		get_uid(t_file **tmp, uid_t st_uid, gid_t st_gid)
{
	struct passwd	*usr;

	(*tmp)->user_del = 0;
	(*tmp)->grp_del = 0;
	errno = 0;
	if (!(usr = getpwuid(st_uid)))
	{
		if (errno)
			return (-1);
		if (!((*tmp)->uid = ft_itoa(st_uid)))
			return (-1);
		(*tmp)->user_del = 1;
	}
	else
		(*tmp)->uid = usr->pw_name;
	return (get_gid(tmp, st_gid));
}
