/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:22:49 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/22 15:23:34 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_pwd(char **new_pwd, char ***env, char opt_p)
{
	char	**new_var;

	if (opt_p)
		ft_strdel(&(*new_pwd));
	if (opt_p)
		*new_pwd = getcwd(NULL, 0);
	new_var = ft_createtab_for_setenv("OLDPWD", ft_getenv("PWD", *env), 'R');
	if (!new_var)
		new_var = ft_createtab_for_setenv("OLDPWD", "/", 'N');
	ft_setenv(new_var, env);
	ft_freetab(&new_var);
	new_var = ft_createtab_for_setenv("PWD", *new_pwd, 'N');
	ft_setenv(new_var, env);
	ft_freetab(&new_var);
}

char	*ft_getenv(char *var, char **env)
{
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)) &&
			env[i][ft_strlen(var)] == '=')
		{
			return (ft_strdup(&env[i][ft_strlen(var) + 1]));
		}
		i++;
	}
	return (NULL);
}

void	ft_increase_shlvl(char ***env)
{
	char	*new_shlvl;
	char	**tab_prompt;
	int		shlvl;

	new_shlvl = ft_getenv("SHLVL", *env);
	if (!new_shlvl)
		tab_prompt = ft_createtab_for_setenv("SHLVL", "1", 'N');
	else
	{
		shlvl = ft_atoi(new_shlvl);
		shlvl++;
		ft_strdel(&new_shlvl);
		new_shlvl = ft_itoa(shlvl);
		tab_prompt = ft_createtab_for_setenv("SHLVL", new_shlvl, 'R');
	}
	ft_setenv(tab_prompt, env);
	ft_freetab(&tab_prompt);
}

char	**ft_createtab_for_setenv(char *name, char *value, char f)
{
	char	**tab;

	if (!name || !value || !(tab = (char **)malloc(sizeof(char *) * 3)))
		return (NULL);
	tab[0] = ft_strdup("setenv");
	tab[1] = ft_strjoin(name, "=", 'N');
	tab[1] = ft_strjoin(tab[1], value, 'L');
	tab[2] = NULL;
	if (f == 'L' || f == 'B')
		ft_strdel(&name);
	if (f == 'R' || f == 'B')
		ft_strdel(&value);
	return (tab);
}

char	**ft_create_env(char **env)
{
	char	**new_env;
	char	**new_var;
	char	*check;

	if (!(new_env = ft_tabdup(env)))
		return (NULL);
	if (!(check = ft_getenv("PATH", new_env)))
	{
		new_var = ft_createtab_for_setenv("PATH", "/bin/", 'N');
		ft_setenv(new_var, &new_env);
		ft_freetab(&new_var);
	}
	else
		ft_strdel(&check);
	if (!(check = ft_getenv("PWD", new_env)))
	{
		new_var = ft_createtab_for_setenv("PWD", getcwd(NULL, 0), 'R');
		ft_setenv(new_var, &new_env);
		ft_freetab(&new_var);
	}
	else
		ft_strdel(&check);
	ft_increase_shlvl(&new_env);
	return (new_env);
}
