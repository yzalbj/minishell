/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:59:15 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/17 14:59:16 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_display_prompt(char **env)
{
	char		*pwd;

	pwd = ft_getenv("PWD", env);
	ft_putstr("\e[32m");
	if (pwd)
		ft_putstr(pwd);
	else
		ft_putchar('$');
	ft_putstr("\e[0m");
	ft_putstr(" > ");
	ft_strdel(&pwd);
}

void ft_manage_prompt(char ***tab_prompt, char *prompt, char **env)
{
	int		i;
	char	*home_env;

	i = 0;
	*tab_prompt = ft_strsplit(prompt, ' ');
	while (*tab_prompt && (*tab_prompt)[i])
	{
		(*tab_prompt)[i] = ft_strtrim((*tab_prompt)[i]);
		if ((*tab_prompt)[i][0] == '~')
		{
			home_env = ft_getenv("HOME", env);
			(*tab_prompt)[i] = ft_strjoin(home_env, &(*tab_prompt)[i][1], 'L');
		}
		i++;
	}
}
