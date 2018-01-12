/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:27:52 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/17 12:21:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*new_list;

	new_list = NULL;
	if (!f)
		return (NULL);
	while (lst)
	{
		if (!(new = ft_lstnew(lst->content, lst->content_size)))
		{
			if (new_list)
				ft_lstdel(&new_list, &ft_lstdelelem);
			return (NULL);
		}
		new = f(lst);
		if (!new_list)
			new_list = new;
		else
			ft_lstaddback(&new_list, new);
		lst = lst->next;
	}
	return (new_list);
}
