/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:29:04 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 14:27:32 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!(new->content = (t_list *)malloc(sizeof(char) * content_size)))
		return (NULL);
	if (content)
		new->content = ft_memcpy(new->content, (void *)content, content_size);
	else
		new->content = NULL;
	new->content_size = (!content ? 0 : content_size);
	new->next = NULL;
	return (new);
}
