/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:09:06 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/23 17:49:36 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	STRREPLACE RETURNS A NEW STRING WHERE THE STRING TO_REPLACE TAKES THE PLACE,
**	IN THE SRC STRING, OF THE INDEX BEGIN TO END. IF TO_REPLACE IS NULL, IT
**	RETURNS A THE STRING SRC OF SIZE BEGIN.
*/

char	*ft_strreplace(char *src, char *to_replace, size_t begin, size_t end)
{
	char	*new;

	if (end < begin || !src)
		return (NULL);
	if (!(new = ft_strnew(begin)))
		return (NULL);
	ft_strncpy(new, src, begin);
	new = ft_strjoin(new, to_replace, 'L');
	new = ft_strjoin(new, &src[end], 'L');
	return (new);
}
