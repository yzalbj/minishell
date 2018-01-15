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
	opt.L = 0;
	opt.P = 0;
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

void	ft_end_cd(int cd_ret, char *path, char ***env)
{
	ft_putendl(path);
	if (!cd_ret || path)
		ft_update_pwd(path, env);
	else
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(path, 2);
	}
}

/*
**	WHEN TO ADD IS NULL, WE ADD THE PWD TO PATH
*/

char	*ft_concatpath(char *path, char **env, char *to_add)
{
	char	*tmp;
	int		i;

	if (!to_add)
		tmp = ft_strdup(ft_getenv("PWD", env));
	else
		tmp = ft_strdup(to_add);
	i = 0;
	while (tmp[i + 1])
		i++;
	if (tmp[i] != '/')
		tmp = ft_strjoin(tmp, "/", 'L');
	path = ft_strjoin(tmp, path, 'L');
	return (path);
}

void ft_checkpath(char *path, char ***env)
{
		char		**cdpath;
		char		*path_tmp;
		struct stat	stat_tmp;
		int			i;

		cdpath = ft_strsplit(ft_getenv("CDPATH", *env), ':');
		path_tmp = NULL;
		i = 0;
		while (cdpath)
		{
			path_tmp = ft_concatpath(path, *env, cdpath[i]);
			if (!lstat(path_tmp, &stat_tmp))
			{
				if ((stat_tmp.st_mode & S_IFDIR) == S_IFDIR)
				{
					ft_freetab(&cdpath);
					break;
					// ft_end_cd(chdir(path_tmp), path_tmp, env);
				}
			}
			ft_strdel(&path_tmp);
			i++;
		}
		if (!path_tmp)
			path_tmp = ft_concatpath(path, *env, NULL);
		if (!lstat(path_tmp, &stat_tmp))
		{
			if ((stat_tmp.st_mode & S_IFDIR) == S_IFDIR)
				ft_end_cd(chdir(path_tmp), path_tmp, env);
		}
		else
			ft_end_cd(-1, path, env);
}

char	*ft_shortpath(char *path, int i, int j)
{
	while (path[i])
	{
		if (!ft_strncmp(&path[i], "/.", 2) &&
			(path[i + 2] == '/' || !path[i + 2]))
		{
			path = ft_strshort(path, i, 2, 1);
			i = 0;
		}
		else if (!ft_strncmp(&path[i], "/..", 3) &&
			(path[i + 3] == '/' || !path[i + 3]))
		{
			j = i > 0 ? i - 1 : 0;
			while (j && path[j] != '/')
				j--;
			if (!path[i + 3])
				path = ft_strshort(path, j + 1, i - j + 2, 1);
			else
				path = ft_strshort(path, j + 1, i - j + 3, 1);
			i = 0;
		}
		else if (path[i] == '/' && path[i + 1] == '/')
			path = ft_strshort(path, i, 1, 1);
		else
			i++;
	}
	return (path);
}

int	ft_cd(t_prompt *p, char ***env)
{
	char	*path;
	t_opt	opt;
	int		i;

	opt = ft_create_option(p->tab_prompt, &i);
	path = ft_strdup(p->tab_prompt[i]);
	if (!path)
	{
		if ((path = ft_strdup(ft_getenv("HOME", *env))))
			ft_end_cd(chdir(path), path, env);
		else
			ft_putendl_fd("cd: HOME not set.", 2);
	}
	else
	{
		if (!ft_strcmp(path, "-"))
		{
			path = ft_getenv("OLDPWD", *env);
			if (path)
				ft_end_cd(chdir(path), path, env);
			else
				ft_putendl_fd("cd: OLDPWD not set.", 2);
		}
		else if (path[0] == '/' || !ft_strncmp(path, "./", 2) ||
			!ft_strncmp(path, "../", 3))
		{
			if (opt.P)
				ft_end_cd(chdir(path), path, env);
			if (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "../", 3))
				path = ft_concatpath(path, *env, NULL);
			path = ft_shortpath(path, 0, 0);
			// ft_putendl(path);
			ft_end_cd(chdir(path), path, env);
		}
		else
			ft_checkpath(path, env);
	}
	return (1);
}
