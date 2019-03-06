/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detail_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocohen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:54:28 by jocohen           #+#    #+#             */
/*   Updated: 2018/04/20 15:43:06 by jocohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_ls.h"

void	put_type_format(t_file *tmp, char *format, t_padd padd, int *type)
{
	if (tmp->mode == 6)
	{
		if (*type != 3)
			set_format(tmp, format, padd, tmp->user_del);
		*type = 3;
	}
	else if (tmp->mode == 2 || tmp->mode == 4)
	{
		if (*type != 2)
			set_format(tmp, format, padd, tmp->user_del);
		*type = 2;
	}
	else
	{
		if (*type != 1)
			set_format(tmp, format, padd, tmp->user_del);
		*type = 1;
	}
}

void	readlink_err(char *format, char *str)
{
	int		x;

	x = 0;
	write(2, "ls: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	perror(0);
	while (format[x])
		x += 1;
	while (x && format[x - 1] != '-' && format[x] != '>')
		x -= 1;
	format[x - 2] = '\n';
	x -= 1;
	while (format[x])
	{
		format[x] = 0;
		x += 1;
	}
}

int		link_display(t_file *tmp, char *path, char *format, int g)
{
	ssize_t		buf_size;
	char		*str;
	char		rights[12];
	char		link_direction[PATH_MAX];

	ft_bzero(link_direction, PATH_MAX);
	(!ft_strcmp(path, ".")) ? path = 0 : 0;
	if (!(str = get_right_path(path, tmp->file_id)))
		return (0);
	get_rights(tmp, rights, str);
	buf_size = readlink(str, link_direction, PATH_MAX);
	(buf_size == -1) ? readlink_err(format, str) : 0;
	ft_memdel((void **)&str);
	(buf_size != -1) ? link_direction[buf_size] = 0 : 1;
	str = link_direction;
	if (!g)
		ft_printf(format, rights, tmp->n_hlink, tmp->uid, tmp->gid,
			tmp->size, get_time(tmp), tmp->file_id, str);
	else
		ft_printf(format, rights, tmp->n_hlink, tmp->gid, tmp->size,
			get_time(tmp), tmp->file_id, str);
	return (1);
}

int		block_chr_display(t_file *tmp, char *format, const char *path, int g)
{
	char	rights[12];
	char	*str;

	if (!(str = get_right_path(path, tmp->file_id)))
		return (0);
	get_rights(tmp, rights, str);
	ft_memdel((void **)&str);
	if (!g)
	{
		if ((ft_printf(format, rights, tmp->n_hlink, tmp->uid, tmp->gid,
			tmp->maj, tmp->min, get_time(tmp), tmp->file_id)) == -1)
			return (0);
	}
	else if ((ft_printf(format, rights, tmp->n_hlink, tmp->gid,
		tmp->maj, tmp->min, get_time(tmp), tmp->file_id)) == -1)
		return (0);
	return (1);
}

int		normal_l_display(t_file *tmp, char *format, const char *path, int g)
{
	char	rights[12];
	char	*str;

	if (!(str = get_right_path(path, tmp->file_id)))
		return (0);
	get_rights(tmp, rights, str);
	ft_memdel((void **)&str);
	if (!g)
	{
		if ((ft_printf(format, rights, tmp->n_hlink, tmp->uid, tmp->gid,
			tmp->size, get_time(tmp), tmp->file_id)) == -1)
			return (0);
	}
	else if ((ft_printf(format, rights, tmp->n_hlink, tmp->gid, tmp->size,
		get_time(tmp), tmp->file_id)) == -1)
		return (0);
	return (1);
}
