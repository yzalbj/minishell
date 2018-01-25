/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 12:31:53 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/17 12:31:58 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_echo(t_shell *s)
{
	int		i;
	char	*tmp;

	i = 1;
	while (s->tab_prompt[i])
	{
		if (!(tmp = ft_strchr(s->tab_prompt[i], '$')) ||
			((tmp = ft_strchr(s->tab_prompt[i], '$')) && !*(tmp + 1)))
		{
			ft_putstr(s->tab_prompt[i]);
			ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
	return (1);
}
