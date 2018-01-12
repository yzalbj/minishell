/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:56:08 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/21 19:41:10 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelelem(void *content, size_t content_size)
{
	size_t	i;

	i = 0;
	if (!content)
		return ;
	while (i < content_size)
	{
		free(content);
		i++;
	}
}
