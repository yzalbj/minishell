/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 11:54:41 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/11 12:22:31 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	STRNJOIN AJOUTE N CHAR DE S2 A S1
*/

char	*ft_strnjoin(char const *s1, char const *s2, size_t n, char c)
{
	char	*str;

	if (!s1 || !s2 || !n)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(s1) + n)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strncpy(&str[ft_strlen(s1)], s2, n);
	ft_freejoin(&s1, &s2, c);
	return (str);
}
