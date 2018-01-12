/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 11:35:32 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 20:18:21 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_intlen(unsigned int nb)
{
	char len;

	len = 1;
	if (!nb)
		return (len);
	while ((nb = nb / 10) != 0)
		len++;
	return (len);
}
