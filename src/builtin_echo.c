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

int		ft_echo(t_shell *s, char **env)
{
	int		i;

	i = 1;
	if (!env)
		ft_putendl("ah");
	while (s->tab_prompt[i])
	{
		ft_putstr(s->tab_prompt[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}
