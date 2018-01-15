/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:54:32 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/10 14:54:45 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void ft_update_pwd(char *new_pwd, char ***env)
{
	char	**new_var;

	new_var = ft_createtab_for_setenv("OLDPWD",
		ft_getenv("PWD", *env), 'N');
	ft_setenv(new_var, env);
	ft_freetab(&new_var);
	new_var = ft_createtab_for_setenv("PWD", new_pwd, 'R');
	ft_setenv(new_var, env);
}

char	*ft_getenv(char *var, char **env)
{
	int		i;

	i = 0;
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

void ft_increase_shlvl(char **env)
{
	char	*new_shlvl;
	char	**tab_prompt;
	int		shlvl;

	new_shlvl = ft_strdup(ft_getenv("SHLVL", env));
	shlvl = ft_atoi(new_shlvl);
	shlvl++;
	tab_prompt = ft_createtab_for_setenv("SHLVL", ft_itoa(shlvl), 'R');
	ft_setenv(tab_prompt, &env);
}

char	**ft_createtab_for_setenv(char *name, char *value, char f)
{
	char	**tab;

	if (!(tab = (char **)malloc(sizeof(char *) * 4)))
		return (NULL);
	tab[0] = ft_strdup("setenv");
	tab[1] = ft_strdup(name);
	tab[2] = ft_strdup(value);
	tab[3] = NULL;
	if (f == 'L' || f == 'B')
		ft_strdel(&name);
	if (f == 'R' || f == 'B')
		ft_strdel(&value);
	return (tab);
}

char	**ft_create_env(char **env)
{
	char	**new_env;
	char	*pwd;

	new_env = NULL;
	if (env && *env)
	{
		new_env = ft_tabdup(env);
		ft_increase_shlvl(new_env);
		return (new_env);
	}
	if (!(new_env = (char **)malloc(sizeof(char *) * 4)))
		return (NULL);
	new_env[0] = ft_strdup("PATH=/bin/");
	if (!(pwd = ft_strnew(256)))
		return (NULL);
	new_env[1] = ft_strjoin("PWD=", getcwd(pwd, 256), 'N');
	new_env[2] = ft_strdup("SHLVL=1");
	new_env[3] = NULL;
	return (new_env);
}
