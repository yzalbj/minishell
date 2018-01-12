/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:50:49 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/07 16:05:14 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	FONCTION QUI PERMET DE FREE UN STRJOIN, L POUR FREE LEFT(s1), R POUR s2,
**	B POUR LES DEUX, N POUR RIEN FREE
*/

void	ft_freejoin(const char **s1, const char **s2, char c)
{
	if (c == 'L')
		ft_strdel((char **)s1);
	else if (c == 'R')
		ft_strdel((char **)s2);
	else if (c == 'B')
	{
		ft_strdel((char **)s1);
		ft_strdel((char **)s2);
	}
}
