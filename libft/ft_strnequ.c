/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:45:42 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 14:23:08 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (!s1 || !s2)
		return (0);
	if (!n)
		return (1);
	while (s1[index] && s2[index] && index < n - 1 && s1[index] == s2[index])
		index++;
	if (s1[index] == s2[index])
		return (1);
	return (0);
}
