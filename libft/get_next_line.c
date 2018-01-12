/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:38:28 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/09 16:46:06 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_alloc_line(char **line, char *buf, int len)
{
	if (!(*line) && buf[0] == '\n')
	{
		if (!(*line = ft_strnew(0)))
			return (-1);
	}
	else if (!(*line) && buf[0])
	{
		if (!(*line = ft_strndup(buf, len)))
			return (-1);
	}
	else if (buf[0])
	{
		if (!(*line = ft_strnjoin(*line, buf, len, 'L')))
			return (-1);
	}
	return (1);
}

static void		ft_increase_buf(char **buf, char *ref_buf, int len)
{
	if ((*buf)[0] == '\n')
		(*buf)++;
	else
		(*buf) += ((*buf)[len] == '\n') ? len + 1 : len;
	if (!(**buf))
	{
		ft_memdel((void **)&ref_buf);
		(*buf) = NULL;
	}
}

static int		ft_buflen(char **buf, char *ref_buf, char **line, int *flag)
{
	int		len;

	len = 0;
	while ((*buf)[len] && (*buf)[len] != '\n' && len < BUFF_SIZE)
		len++;
	if ((*buf)[len] == '\n')
	{
		if (!(*line) && len == 0)
			len++;
		*flag = 0;
	}
	if (len == 0 && !((*buf)[0]))
		len++;
	if (len > 0 && (ft_alloc_line(line, *buf, len)) == -1)
		return (-1);
	ft_increase_buf(buf, ref_buf, len);
	if (*flag)
		return (1);
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char *buf[2];
	int			flag[2];

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	flag[0] = 1;
	flag[1] = 1;
	*line = NULL;
	while (flag[0] > 0 && flag[1])
	{
		if (!buf[0])
		{
			if (!(buf[0] = ft_strnew(BUFF_SIZE)))
				return (-1);
			if ((flag[1] = read(fd, buf[0], BUFF_SIZE)) < 0)
				return (-1);
			buf[1] = &buf[0][0];
		}
		flag[0] = ft_buflen(&buf[0], buf[1], line, &flag[0]);
	}
	if (flag[0] == -1)
		return (-1);
	if (!(*line) && !flag[1])
		return (0);
	return (1);
}
