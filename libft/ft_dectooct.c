/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectooct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:12:50 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 20:19:33 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_dectooct(int nb)
{
	int		*result;
	int		i;

	i = 0;
	result = (int *)malloc(sizeof(int) * 1000);
	while (nb > 0)
	{
		result[i] = nb % 8;
		nb = nb / 8;
		i++;
	}
	result[i] = -1;
	return (result);
}
