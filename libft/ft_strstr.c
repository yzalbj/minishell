/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:11:59 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/11 16:45:00 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*hay_tmp;
	char	*needle_tmp;

	if (*needle == '\0')
		return ((char *)haystack);
	while ((char)*haystack)
	{
		hay_tmp = (char *)haystack;
		needle_tmp = (char *)needle;
		while (*hay_tmp == *needle_tmp)
		{
			if (*(needle_tmp + 1) == '\0')
				return ((char *)haystack);
			hay_tmp++;
			needle_tmp++;
		}
		haystack++;
	}
	return (NULL);
}
