/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 12:37:08 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/10 12:37:25 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// void ft_exit(t_prompt *p)
// {
// 	exit(0);
// }
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

int	ft_builtin(t_prompt *p)
{
	int		i;

	i = 0;
	while (p->builtin[i])
	{
		if (!ft_strcmp(p->builtin[i], p->tab_prompt[0]) && i == 2)
		{
			p->env = ft_setenv(p->tab_prompt, p->env);
			return (1);
		}
		if (!ft_strcmp(p->builtin[i], p->tab_prompt[0]) && i == 3)
		{
			ft_unsetenv(p->tab_prompt, p->env);
			return (1);
		}
		if (!ft_strcmp(p->builtin[i], p->tab_prompt[0]) && i == 4)
		{
			ft_env(p);
			ft_putendl("after the env yo");
			return (1);
		}
		if (!ft_strcmp(p->builtin[i], p->tab_prompt[0]) && i == 5)
		{
			// if (!p->tab_prompt[1] && p->tab_prompt[2])
			// {
			// 	ft_putendl("exit: too many arguments");
			// 	return (-1);
			// }
			// else
				exit(0);
		}
		i++;
	}
	return (0);
}
