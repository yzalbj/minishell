/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:20 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 17:38:27 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	i;
	size_t	tmp;
	size_t	len;

	len = size - ft_strlen(dst) - 1;
	tmp = ft_strlen(dst);
	i = 0;
	if (tmp < size)
	{
		while (i < len)
		{
			dst[tmp + i] = (char)src[i];
			i++;
		}
		dst[size - 1] = '\0';
		return (tmp + ft_strlen(src));
	}
	return (size + ft_strlen(src));
}
