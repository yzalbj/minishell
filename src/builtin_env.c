/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:54:19 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/23 15:06:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Builtin --> env [-i] [name=value ...] [utility [argument ...]]
*/

void	ft_printerrror(char c)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: env [-i] [name=value ...] [utility", 2);
	ft_putendl_fd("[argument ...]]", 2);
}

void	ft_changetab_forenv(t_shell *s, char ***env, char ***new_env, int *i)
{
	char	**new_var;
	char	**tab_setenv;

	if (!s->tab_prompt[1] || s->tab_prompt[1][0] != '-')
		*new_env = ft_tabdup(*env);
	else if (s->tab_prompt[1] && !ft_strcmp(s->tab_prompt[1], "-i"))
	{
		(*i)++;
		if (!(*new_env = (char **)malloc(sizeof(char *) * 1)))
			return ;
		**new_env = NULL;
	}
	else if (s->tab_prompt[1][0] == '-' && s->tab_prompt[1][1] && !(*i = 0))
		ft_printerrror(s->tab_prompt[1][1]);
	while (*i > 0 && s->tab_prompt[*i] && ft_strchr(s->tab_prompt[*i], '='))
	{
		new_var = ft_strsplit(s->tab_prompt[*i], '=');
		tab_setenv = ft_createtab_for_setenv(new_var[0], new_var[1], 'N');
		ft_freetab(&new_var);
		ft_setenv(tab_setenv, new_env);
		ft_freetab(&tab_setenv);
		(*i)++;
	}
}

void	ft_start_env(t_shell *s, char **new_env, int i)
{
	pid_t	process;
	char	**tmp;

	if (!s->tab_prompt[i])
		ft_printtab(new_env);
	else if (s->tab_prompt[i])
	{
		process = fork();
		if (!process)
		{
			ft_exec(&s->tab_prompt[i], s->builtin, new_env);
			exit(0);
		}
		else
		{
			wait(0);
			tmp = ft_tabdup(s->tab_prompt);
			ft_freetab(&(s->tab_prompt));
			s->tab_prompt = ft_tabdup(tmp + i);
			ft_freetab(&tmp);
			ft_builtin(s, &new_env);
		}
	}
	ft_freetab(&new_env);
}

void	ft_env(t_shell *s, char ***env)
{
	int		i;
	char	**new_env;

	i = 1;
	if (!*env)
		return ;
	ft_changetab_forenv(s, env, &new_env, &i);
	if (!i)
		return ;
	ft_start_env(s, new_env, i);
}
