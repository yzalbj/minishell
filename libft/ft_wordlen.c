/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:22:02 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 15:59:48 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_wordlen(char const *s, char c)
{
	unsigned int	len;

	len = 0;
	while (s && s[len] && s[len] != c)
		len++;
	return (len);
}
