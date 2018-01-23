/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:37:11 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/23 17:20:21 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_end_cd(int cd_ret, char *path, char ***env, char opt_p)
{
	if (!cd_ret)
	{
		if (opt_p)
			path = getcwd(NULL, 0);
		ft_update_pwd(path, env);
	}
	else if (cd_ret == -2)
	{
		ft_putstr_fd("cd: Not a directory: ", 2);
		ft_putendl_fd(path, 2);
		ft_strdel(&path);
	}
	else if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		ft_strdel(&path);
	}
	else if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putendl_fd(path	, 2);
		ft_strdel(&path);
	}
}

char	*ft_check_cdpath(char *path, char ***env)
{
	char		**cdpath;
	char		*path_tmp;
	struct stat	stat_tmp;
	int			i;

	path_tmp = NULL;
	cdpath = ft_strsplit(ft_getenv("CDPATH", *env), ':');
	i = 0;
	while (cdpath && cdpath[i])
	{
		path_tmp = ft_concatpath(path, *env, cdpath[i]);
		if (!lstat(path_tmp, &stat_tmp))
		{
			if ((stat_tmp.st_mode & S_IFDIR) == S_IFDIR)
			{
				ft_freetab(&cdpath);
				break ;
			}
		}
		ft_strdel(&path_tmp);
		i++;
	}
	return (path_tmp);
}

char	*ft_checkpath(char *path, char ***env, char opt_p)
{
	char		*path_tmp;
	struct stat	stat_tmp;

	path_tmp = NULL;
	path_tmp = ft_check_cdpath(path, env);
	if (!path_tmp)
		path_tmp = ft_concatpath(path, *env, NULL);
	if (!opt_p)
		ft_shortpath(&path_tmp, 0, 0);
	if (!lstat(path_tmp, &stat_tmp))
	{
		if ((stat_tmp.st_mode & S_IFDIR) == S_IFDIR ||
				(stat_tmp.st_mode & S_IFLNK) == S_IFLNK)
			return (path_tmp);
		else
			ft_end_cd(-2, path, env, opt_p);
	}
	else
		ft_end_cd(-1, path, env, opt_p);
	return (NULL);
}

void	ft_cd2(char *path, char opt_p, char ***env)
{
	if (path[0] == '/' || !ft_strncmp(path, "./", 2) ||
		!ft_strncmp(path, "../", 3))
	{
		if (*env && (!ft_strncmp(path, "./", 2) ||
				!ft_strncmp(path, "../", 3)))
			path = ft_concatpath(path, *env, NULL);
		if (*env && !opt_p)
			ft_shortpath(&path, 0, 0);
	}
	else if (*env)
		path = ft_checkpath(path, env, opt_p);
	if (path)
		ft_end_cd(chdir(path), path, env, opt_p);
}

void	ft_cd(t_shell *s, char ***env)
{
	char	*path;
	char	opt_p;
	int		i;

	opt_p = ft_isoptp(s->tab_prompt, &i);
	path = ft_strdup(s->tab_prompt[i]);
	if (s->tab_prompt[i + 1] && s->tab_prompt[1])
		ft_putendl_fd("cd: Too many arguments.", 2);
	else if (!path)
	{
		if (*env && (path = ft_getenv("HOME", *env)))
			ft_end_cd(chdir(path), path, env, opt_p);
		else
			ft_putendl_fd("cd: HOME not set.", 2);
	}
	else if (!ft_strcmp(path, "-"))
	{
		path = (*env) ? ft_getenv("OLDPWD", *env) : NULL;
		if (path)
			ft_end_cd(chdir(path), path, env, opt_p);
		else
			ft_putendl_fd("cd: OLDPWD not set.", 2);
	}
	else
		ft_cd2(path, opt_p, env);
}
