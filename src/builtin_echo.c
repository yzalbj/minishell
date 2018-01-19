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
	char	*var_env;

	i = 1;
	while (s->tab_prompt[i])
	{
		if (s->tab_prompt[i][0] == '$' && s->tab_prompt[i][1])
		{
			var_env = ft_getenv(&s->tab_prompt[i][1], env);
			ft_putstr(var_env);
			ft_putchar(' ');
			ft_strdel(&var_env);
		}
		else
		{
			ft_putstr(s->tab_prompt[i]);
			ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
	return (1);
}
