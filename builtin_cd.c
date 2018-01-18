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

char	ft_isoptp(char **tab_prompt, int *i)
{
	char	opt_p;
	int		j;

	*i = 1;
	opt_p = 0;
	while (tab_prompt[*i] &&
		tab_prompt[*i][0] == '-' && tab_prompt[*i][1])
	{
		j = 1;
		while (tab_prompt[*i][j] &&
			(tab_prompt[*i][j] == 'L' || tab_prompt[*i][j] == 'P'))
		{
			if (tab_prompt[*i][j] == 'P')
				opt_p = 1;
			j++;
		}
		if (tab_prompt[*i][j] &&
			(tab_prompt[*i][j] != 'L' || tab_prompt[*i][j] != 'P'))
			break ;
		(*i)++;
	}
	return (opt_p);
}

void	ft_end_cd(int cd_ret, char *path, char ***env, char opt_p)
{
	if (!cd_ret)
	{
		if (opt_p)
			path = getcwd(NULL, 0);
		ft_update_pwd(path, env);
	}
	if (cd_ret == -2)
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

char	*ft_checkpath(char *path, char ***env, char opt_p)
{
		char		**cdpath;
		char		*path_tmp;
		struct stat	stat_tmp;
		int			i;

		cdpath = ft_strsplit(ft_getenv("CDPATH", *env), ':');
		path_tmp = NULL;
		i = 0;
		while (cdpath && cdpath[i])
		{
			path_tmp = ft_concatpath(path, *env, cdpath[i]);
			if (!lstat(path_tmp, &stat_tmp))
			{
				if ((stat_tmp.st_mode & S_IFDIR) == S_IFDIR)
				{
					ft_freetab(&cdpath);
					break;
				}
			}
			ft_strdel(&path_tmp);
			i++;
		}
		if (!path_tmp)
			path_tmp = ft_concatpath(path, *env, NULL);
		if (!opt_p)
			path_tmp = ft_shortpath(path_tmp, 0, 0);
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

int	ft_cd(t_prompt *p, char ***env)
{
	char	*path;
	char	opt_p;
	int		i;

	opt_p = ft_isoptp(p->tab_prompt, &i);
	path = ft_strdup(p->tab_prompt[i]);
	if (!path)
	{
		if (*env && (path = ft_strdup(ft_getenv("HOME", *env))))
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
	{
		if (path[0] == '/' || !ft_strncmp(path, "./", 2) ||
			!ft_strncmp(path, "../", 3))
		{
			if (*env && (!ft_strncmp(path, "./", 2) || !ft_strncmp(path, "../", 3)))
				path = ft_concatpath(path, *env, NULL);
			if (*env && !opt_p)
				path = ft_shortpath(path, 0, 0);
		}
		else if (*env)
			path = ft_checkpath(path, env, opt_p);
		if (path)
			ft_end_cd(chdir(path), path, env, opt_p);
	}
	return (1);
}
