/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:59:15 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/22 15:17:37 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_display_prompt(char **env)
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

void	ft_rmtab(char **prompt)
{
	int		i;
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
	ft_strdel(prompt);
	*prompt = ft_strdup(new);
	ft_strdel(&new);
}

char	*ft_rpl_tilde(char *prompt, char **env)
{
	size_t		i;
	char		*var_home;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '~' && (prompt[i + 1] == '/' || !prompt[i + 1]))
		{
			if ((var_home = ft_getenv("HOME", env)))
			{
				prompt = ft_strreplace(prompt, var_home, i, i + 1);
				i = i + ft_strlen(var_home);
			}
		}
		i++;
	}
	return (prompt);
}

char	*ft_rpl_dollars(char *prompt, char **env)
{
	int		i;
	int		j;
	char	*to_search;
	char	*var_env;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '$' && prompt[i + 1])
		{
			j = i + 1;
			while (prompt[j] && prompt[j] != '/' && prompt[j] != '$')
				j++;
			to_search = ft_strndup(&prompt[i + 1], j - i);
			if ((var_env = ft_getenv(to_search, env)))
			{
				prompt = ft_strreplace(prompt, var_env, i, j);
				i = j;
			}
		}
		i++;
	}
	return (prompt);
}

void	ft_manage_prompt(t_shell *s)
{
	ft_display_prompt(s->env);
	signal(SIGINT, &ft_control_c);
	s->prompt = NULL;
	if (!get_next_line(0, &(s->prompt)))
		ft_exit(s, 0);
	ft_rmtab(&(s->prompt));
	s->prompt = ft_rpl_tilde(s->prompt, s->env);
	s->prompt = ft_rpl_dollars(s->prompt, s->env);
	s->tab_prompt = ft_strsplit(s->prompt, ' ');
}
