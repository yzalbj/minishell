/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:22:07 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 14:20:59 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*ptr_s1;
	char	*ptr_s2;

	i = 0;
	ptr_s1 = (char *)s1;
	ptr_s2 = (char *)s2;
	if (!n)
		return (0);
	while (i + 1 < n && ptr_s1[i] == ptr_s2[i])
		i++;
	return ((unsigned char)ptr_s1[i] - (unsigned char)ptr_s2[i]);
}
