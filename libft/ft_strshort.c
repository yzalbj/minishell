/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 10:48:33 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/15 10:48:47 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strshort(char *str, int index, int len, char f)
{
	char	*new;
	int		size;

	size = ft_strlen(str) - len;
	new = NULL;
	if (size > -1 && !(new = ft_strnew(size)))
		return (NULL);
	ft_strncpy(new, str, index);
	ft_strcpy(&new[index], &str[index + len]);
	if (f > 0)
		ft_strdel(&str);
	return (new);
}
