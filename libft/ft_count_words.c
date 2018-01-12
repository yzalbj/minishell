/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:08:14 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 15:57:46 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_count_words(char const *s, char c)
{
	unsigned int	count;
	unsigned int	flag;
	size_t			index;

	count = 0;
	index = 0;
	flag = 1;
	if (!s)
		return (0);
	while (s[index])
	{
		if (s[index] != c && flag == 1)
		{
			count++;
			flag = 0;
		}
		if (s[index] == c)
			flag = 1;
		index++;
	}
	return (count);
}
