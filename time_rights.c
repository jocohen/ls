/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 12:39:53 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/16 14:22:06 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

char	get_attributes(char *path_file)
{
	acl_t		lst;
	ssize_t		x;

	x = listxattr(path_file, 0, 0, 0);
	if (!x || x == -1)
	{
		if (!(lst = acl_get_link_np(path_file, ACL_TYPE_EXTENDED)))
			return (' ');
		else
		{
			acl_free((void *)lst);
			return ('+');
		}
	}
	else
		return ('@');
}

char	file_type(int mode)
{
	char	out;

	out = '-';
	(mode == 1) ? out = 'p' : 1;
	(mode == 2) ? out = 'c' : 1;
	(mode == 3) ? out = 'd' : 1;
	(mode == 4) ? out = 'b' : 1;
	(mode == 6) ? out = 'l' : 1;
	(mode == 7) ? out = 's' : 1;
	return (out);
}

void	get_rights(t_file *tmp, char rights[12], char *path_file)
{
	ft_memset(rights, '-', 10);
	rights[0] = file_type(tmp->mode);
	(tmp->perm & S_IRUSR) ? rights[1] = 'r' : 1;
	(tmp->perm & S_IWUSR) ? rights[2] = 'w' : 1;
	(tmp->perm & S_IXUSR) ? rights[3] = 'x' : 1;
	(!(tmp->perm & S_IXUSR) && (tmp->perm & S_ISUID)) ? rights[3] = 'S' : 1;
	((tmp->perm & S_IXUSR) && (tmp->perm & S_ISUID)) ? rights[3] = 's' : 1;
	(tmp->perm & S_IRGRP) ? rights[4] = 'r' : 1;
	(tmp->perm & S_IWGRP) ? rights[5] = 'w' : 1;
	(tmp->perm & S_IXGRP) ? rights[6] = 'x' : 1;
	(!(tmp->perm & S_IXGRP) && (tmp->perm & S_ISGID)) ? rights[6] = 'S' : 1;
	((tmp->perm & S_IXGRP) && (tmp->perm & S_ISGID)) ? rights[6] = 's' : 1;
	(tmp->perm & S_IROTH) ? rights[7] = 'r' : 1;
	(tmp->perm & S_IWOTH) ? rights[8] = 'w' : 1;
	(tmp->perm & S_IXOTH) ? rights[9] = 'x' : 1;
	(!(tmp->perm & S_IXOTH) && (tmp->perm & S_ISVTX)) ? rights[9] = 'T' : 1;
	((tmp->perm & S_IXOTH) && (tmp->perm & S_ISVTX)) ? rights[9] = 't' : 1;
	rights[10] = get_attributes(path_file);
}

char	*get_time(t_file *tmp)
{
	char		*modif_tim;

	modif_tim = ctime(&tmp->m_time);
	if ((time(0) - tmp->m_time) > 15778458 || ((time(0) - tmp->m_time)
	< -15778458))
	{
		ft_memmove(modif_tim, modif_tim + 3, 8);
		if (tmp->m_time >= 253402297200)
			ft_memmove(modif_tim + 8, modif_tim + 23, 6);
		else
			ft_memmove(modif_tim + 8, modif_tim + 19, 5);
	}
	else
		ft_memmove(modif_tim, modif_tim + 3, 13);
	if (tmp->m_time >= 253402297200)
	{
		modif_tim[14] = ' ';
		modif_tim[15] = 0;
		return (modif_tim);
	}
	modif_tim[13] = ' ';
	modif_tim[14] = 0;
	return (modif_tim);
}
