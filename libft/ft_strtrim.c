/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:19:06 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 19:15:30 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	begin;
	size_t	end;
	char	*str;

	begin = 0;
	if (!s)
		return (NULL);
	end = ft_strlen(s);
	while ((s[begin] == ' ' || s[begin] == 9 || s[begin] == 10) && s[begin])
		begin++;
	while ((s[end - 1] == ' ' || s[end - 1] == '\t' ||
				s[end - 1] == '\n') && end != begin)
		end--;
	str = (char *)malloc(sizeof(char) * (end - begin) + 1);
	if (!str)
		return (NULL);
	ft_strncpy(str, &s[begin], end - begin);
	str[end - begin] = '\0';
	return (str);
}
