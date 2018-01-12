/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:53:33 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/13 12:58:03 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	index;

	index = 0;
	if (!s || !(str = ft_strnew(len)))
		return (NULL);
	while (index < len)
	{
		str[index] = s[start + index];
		index++;
	}
	return (str);
}
