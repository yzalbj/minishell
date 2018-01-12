/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:27:04 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/16 18:36:17 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	unsigned int	count;
	size_t			index;
	char			*begin;
	char			**tab;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	begin = (char *)s - 1;
	index = 0;
	if ((tab = (char **)malloc(sizeof(char *) * (count + 1))) == NULL)
		return (NULL);
	while (index < count)
	{
		if (*s && *s != c && (*(s - 1) == c || begin == s - 1))
		{
			if (!(tab[index] = ft_strnew(ft_wordlen(s, c))))
				return (NULL);
			ft_strncpy(tab[index], s, ft_wordlen(s, c));
			tab[index++][ft_wordlen(s, c)] = '\0';
		}
		s++;
	}
	tab[index] = NULL;
	return (tab);
}
