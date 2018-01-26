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

void	ft_display_prompt(void)
{
	char		*pwd;

	pwd = ft_strdup((ft_singleton_sh(NULL))->pwd);
	ft_putstr("\e[32m");
	if (pwd)
		ft_putstr(pwd);
	else
		ft_putchar('$');
	ft_putstr("\e[0m");
	ft_putstr(" > ");
	ft_strdel(&pwd);
}

void	ft_rmtab(char **prompt, int i, int j)
{
	char	*new;

	while ((*prompt)[i])
	{
		(*prompt)[i] != '"' && (*prompt)[i] != '\'' ? j++ : 0;
		i++;
	}
	if (!(new = ft_strnew(j)))
		return ;
	i = 0;
	j = 0;
	while ((*prompt)[i])
	{
		if ((*prompt)[i] != '\t' && (*prompt)[i] != '"' && (*prompt)[i] != '\'')
			new[j] = (*prompt)[i];
		else if ((*prompt)[i] != '"' && (*prompt)[i] != '\'')
			new[j] = ' ';
		(*prompt)[i] != '"' && (*prompt)[i] != '\'' ? j++ : 0;
		i++;
	}
	ft_strdel(prompt);
	*prompt = ft_strdup(new);
	ft_strdel(&new);
}

char	*ft_rpl_tilde(char *prompt, char **env, size_t *i)
{
	char		*var_home;
	char		*tmp;

	if ((var_home = ft_getenv("HOME", env)))
	{
		tmp = ft_strreplace(prompt, var_home, *i, *i + 1);
		ft_strdel(&prompt);
		prompt = tmp;
		*i = *i + ft_strlen(var_home) - 1;
		ft_strdel(&var_home);
	}
	return (prompt);
}

char	*ft_rpl_dollars(char *prompt, char **env, size_t *i)
{
	size_t	j;
	char	*to_search;
	char	*var_env;
	char	*tmp;

	j = *i + 1;
	while (prompt[j] && prompt[j] != '/' &&
		prompt[j] != '$' && ft_isalnum(prompt[j]))
		j++;
	to_search = ft_strndup(&prompt[*i + 1], j - *i - 1);
	if ((var_env = ft_getenv(to_search, env)))
	{
		tmp = ft_strreplace(prompt, var_env, *i, j);
		ft_strdel(&prompt);
		prompt = tmp;
		ft_strdel(&var_env);
		*i = 0;
	}
	ft_strdel(&to_search);
	return (prompt);
}

void	ft_manage_prompt(t_shell *s)
{
	size_t	i;

	i = 0;
	ft_display_prompt();
	signal(SIGINT, &ft_control_c);
	s->prompt = NULL;
	if (!get_next_line(0, &(s->prompt)))
		ft_exit(s, 0);
	ft_rmtab(&(s->prompt), 0, 0);
	while (s->prompt[i])
	{
		if (s->prompt[i] == '~' && (s->prompt[i + 1] == '/'
			|| !s->prompt[i + 1]))
			s->prompt = ft_rpl_tilde(s->prompt, s->env, &i);
		if (s->prompt[i] == '$' && s->prompt[i + 1])
			s->prompt = ft_rpl_dollars(s->prompt, s->env, &i);
		i++;
	}
	s->tab_prompt = ft_strsplit(s->prompt, ' ');
}
