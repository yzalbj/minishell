/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectobin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:26:21 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 20:20:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_dectobin(int nb)
{
	int		*result;
	int		i;

	i = 0;
	result = (int *)malloc(sizeof(int) * 1000);
	while (nb > 0)
	{
		result[i] = nb % 2;
		nb = nb / 2;
		i++;
	}
	result[i] = -1;
	return (result);
}
