/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:54:30 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/10 17:46:41 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabndup(char **tab, size_t n)
{
	char	**new;
	size_t	i;

	i = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	while (tab[i] && i < n)
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	while (i < n + 1)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}
