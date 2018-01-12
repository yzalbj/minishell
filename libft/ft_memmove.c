/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:43:12 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 16:12:05 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;
	size_t order;

	order = dst > src ? len : 0;
	i = order;
	while ((order == 0 ? (i < len) : (i-- > 0)))
	{
		((char*)dst)[i] = ((char*)src)[i];
		if (!order)
			i++;
	}
	return (dst);
}
