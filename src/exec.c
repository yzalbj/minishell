/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:39:21 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/22 15:23:59 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_error(char *tab_prompt)
{
	ft_putstr_fd(tab_prompt, 2);
	if (access(tab_prompt, X_OK) == -1 && access(tab_prompt, F_OK) == 0)
		ft_putendl_fd(": permission denied.", 2);
	else
		ft_putendl_fd(": command not found.", 2);
}

void	ft_addslash_totab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		tab[i] = ft_strjoin(tab[i], "/", 'L');
		i++;
	}
}

void	ft_exec(char **tab_prompt, char **builtin, char **env)
{
	char	*env_path;
	char	**all_path;
	char	*bin;
	int		i;

	env_path = ft_getenv("PATH", env);
	all_path = ft_strsplit(env_path, ':');
	while (*builtin)
	{
		if (!ft_strcmp(*builtin++, tab_prompt[0]))
			exit(0);
	}
	i = 0;
	ft_addslash_totab(all_path);
	while (all_path && all_path[i])
	{
		bin = ft_strjoin(all_path[i], tab_prompt[0], 'N');
		if (execve(bin, tab_prompt, env))
			i++;
		ft_strdel(&bin);
	}
	execve(tab_prompt[0], tab_prompt, env);
	ft_exec_error(tab_prompt[0]);
	exit(-1);
}
