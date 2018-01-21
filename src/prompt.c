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

void ft_rmtab(char	**prompt)
{
	int	i;
	char	*new;

	new = ft_strnew(ft_strlen((*prompt)));
	i = 0;
	while ((*prompt)[i])
	{
		if ((*prompt)[i] != '\t')
			new[i] = (*prompt)[i];
		else
			new[i] = ' ';
		i++;
	}
	// free(prompt);
	// ft_strdel(prompt);
	prompt = &new;
}

void ft_manage_prompt(char ***tab_prompt, char *prompt, char **env)
{
	int		i;
	int		j[2];
	char	*tmp;
	char	*new;
	char	*var_env;

	i = 1;
	ft_rmtab(&prompt);
	*tab_prompt = ft_strsplit(prompt, ' ');
	while (*tab_prompt && (*tab_prompt)[i])
	{
		if ((*tab_prompt)[i][0] == '~' && ((*tab_prompt)[i][1] == '/'
			|| !(*tab_prompt)[i][1]))
		{
			if ((var_env = ft_getenv("HOME", env)))
				(*tab_prompt)[i] = ft_strjoin(var_env, &(*tab_prompt)[i][1], 'L');
		}
		j[0] = 0;
		j[1] = 0;
		new = ft_strnew(0);
		while ((*tab_prompt)[i][j[0]])
		{
			if ((*tab_prompt)[i][j[0]] == '$')
			{
				tmp = ft_strndup(&(*tab_prompt)[i][j[1]], j[0] - j[1]);
				new = ft_strjoin(new, tmp, 'B');
				j[1] = j[0];
				while ((*tab_prompt)[i][j[1]] && (*tab_prompt)[i][j[1]] != '/')
					j[1]++;
				tmp = ft_strndup(&(*tab_prompt)[i][j[0] + 1], j[1] - j[0] - 1);
				var_env = ft_getenv(tmp, env);
				new = ft_strjoin(new, var_env, 'B');
				j[0] = j[1];
			}
			else
				j[0]++;
		}
		if (j[1])
			(*tab_prompt)[1] = new;
		// else
		// 	ft_strdel(&new);
		i++;
	}
}
