/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:02:45 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/13 13:50:58 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_exception(int n)
{
	char	*result;

	if (n == 0)
	{
		if (!(result = ft_strnew(1)))
			return (NULL);
		ft_strcpy(result, "0");
	}
	else
	{
		if (!(result = ft_strnew(11)))
			return (NULL);
		ft_strcpy(result, "-2147483648");
	}
	return (result);
}

char		*ft_itoa(int n)
{
	size_t	len;
	int		tmp;
	char	*result;

	tmp = n;
	len = 1;
	if (!n || n == -2147483648)
		return (ft_exception(n));
	while ((tmp = tmp / 10) != 0)
		len++;
	if (n < 0)
		len++;
	if ((result = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	result[len] = '\0';
	tmp = ((n < 0) ? -n : n);
	while (tmp)
	{
		result[(len--) - 1] = tmp % 10 + 48;
		tmp = tmp / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
