/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 12:37:08 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/22 15:22:36 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *s, int ex)
{
	ft_strdel(&(s->prompt));
	ft_freetab(&(s->tab_prompt));
	ft_freetab(&(s->builtin));
	exit(ex);
}

char	**create_builtin_tab(void)
{
	char **builtin;

	if (!(builtin = (char **)malloc(sizeof(char *) * 7)))
		return (NULL);
	builtin[0] = ft_strdup("echo");
	builtin[1] = ft_strdup("cd");
	builtin[2] = ft_strdup("setenv");
	builtin[3] = ft_strdup("unsetenv");
	builtin[4] = ft_strdup("env");
	builtin[5] = ft_strdup("exit");
	builtin[6] = NULL;
	return (builtin);
}

int		ft_builtin(t_shell *s, char ***env)
{
	if (!ft_strcmp(s->builtin[0], s->tab_prompt[0]))
		ft_echo(s);
	else if (!ft_strcmp(s->builtin[1], s->tab_prompt[0]))
		ft_cd(s, env);
	else if (!ft_strcmp(s->builtin[2], s->tab_prompt[0]))
		ft_setenv(s->tab_prompt, env);
	else if (!ft_strcmp(s->builtin[3], s->tab_prompt[0]))
		ft_unsetenv(s->tab_prompt, env);
	else if (!ft_strcmp(s->builtin[4], s->tab_prompt[0]))
		ft_env(s, env);
	else if (!ft_strcmp(s->builtin[5], s->tab_prompt[0]))
		ft_exit(s, 0);
	else
		return (0);
	return (1);
}
