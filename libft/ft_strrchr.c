/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:43:39 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/11 16:25:58 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = ft_strlen(s);
	if (ptr[i] == c)
		return (&ptr[i]);
	while (i > 0)
	{
		if (ptr[i - 1] == c)
			return (&ptr[i - 1]);
		i--;
	}
	if (ptr[i - 1] == c)
		return (&ptr[i - 1]);
	return (NULL);
}
