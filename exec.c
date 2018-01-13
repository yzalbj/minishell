/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:39:21 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/10 11:39:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void ft_addslash_totab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		tab[i] = ft_strjoin(tab[i], "/", 'L');
		i++;
	}
}

// void ft_execve(char **tab_prompt, char *bin_to_exec, char **env)
// {
// 	if (execve(bin_to_exec, tab_prompt, env))
// 	{
// 		if (!all_path[i])
// 		{
// 			if (execve(tab_prompt[0], tab_prompt, env))
// 			{
// 				ft_putstr(tab_prompt[0]);
// 				ft_putendl(": command not found.");
// 				break;
// 			}
// 		}
// 		ft_strdel(&bin);
// 	}

void ft_exec(t_prompt *p, char **tab_prompt, char **env)
{
	char	*env_path;
	char	**all_path;
	char	*bin;
	int		i;

	env_path = ft_strdup(ft_getenv("PATH", env));
	all_path = ft_strsplit(env_path, ':');
	i = 0;
	ft_addslash_totab(all_path);
	while (p->builtin[i])
	{
		if (!ft_strcmp(p->builtin[i], tab_prompt[0]))
			return ;
		i++;
	}
	i = 0;
	if (!all_path)
	{
		ft_putstr(tab_prompt[0]);
		ft_putendl(": command not found.");
	}
	while (all_path)
	{
		bin = ft_strjoin(all_path[i], tab_prompt[0], 'N');
		if (execve(bin, tab_prompt, env))
		{
			if (!all_path[i])
			{
				if (execve(tab_prompt[0], tab_prompt, env))
				{
					ft_putstr(tab_prompt[0]);
					ft_putendl(": command not found.");
					break;
				}
			}
			ft_strdel(&bin);
			i++;
		}
		ft_strdel(&bin);
	}
}
