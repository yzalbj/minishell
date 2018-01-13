/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:37:11 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/13 14:37:13 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_opt	ft_create_option(char **tab_prompt, int *i)
{
	t_opt	opt;

	*i = 1;
	while (tab_prompt[*i] && (!ft_strcmp(tab_prompt[*i], "-L") ||
		!ft_strcmp(tab_prompt[*i], "-P")))
	{
		if (!ft_strcmp(tab_prompt[*i], "-L"))
		{
			opt.P = 0;
			opt.L = 1;
		}
		else
		{
			opt.L = 0;
			opt.P = 1;
		}
		(*i)++;
	}
	if (opt.L != 1)
		opt.L = 0;
	if (opt.P != 1)
		opt.P = 0;
	return (opt);
}

void	ft_end_cd(int cd_ret, char *path, char **env)
{
	if (!cd_ret)
		ft_update_pwd(path, env);
	else if (cd_ret == -1)
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(path, 2);
	}
}

int	ft_cd(t_prompt *p, char **env)
{
	char	*path;
	t_opt	opt;
	int		i;
	int		ret;

	opt = ft_create_option(p->tab_prompt, &i);
	path = ft_strdup(p->tab_prompt[i]);
	ret = 1;
	if (!path)
	{
		if ((path = ft_strdup(ft_getenv("HOME", env))))
			ft_end_cd(chdir(path), path, env);
		else
			ft_putendl_fd("cd: HOME not set.", 2);
	}
	else
	{
		i = 0;
		if (path[i] == '/')
		{
			if (opt.P)
				ft_end_cd(chdir(path), path, env);
			while (path[i])
			{
				if (ft_strncmp(&path[i], "/i/", 3))
					//il faudrait creer une fonction qui retire une portion a l;interieur de la string;
				i++;
			}
		}
	}
	return (1);
}
