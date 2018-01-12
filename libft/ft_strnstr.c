/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:01:09 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/11 16:47:52 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay_tmp;
	char	*needle_tmp;
	size_t	index[2];

	index[0] = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (index[0] < len && (char)*haystack)
	{
		hay_tmp = (char *)haystack;
		needle_tmp = (char *)needle;
		index[1] = index[0]++;
		while (index[1] < len && *hay_tmp == *needle_tmp)
		{
			if (*(needle_tmp + 1) == '\0')
				return ((char *)haystack);
			hay_tmp++;
			needle_tmp++;
			index[1]++;
		}
		haystack++;
	}
	return (NULL);
}
