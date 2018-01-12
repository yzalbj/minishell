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


char	*ft_getenv(char *var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)) &&
			env[i][ft_strlen(var)] == '=')
		{
			return (&env[i][ft_strlen(var) + 1]);
		}
		i++;
	}
	return (NULL);
}
//
// void ft_changeenv(char *var, char *new_var, char **env)
// {
// 	char	*to_add;
// 	int		i;
//
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(var, env[i], ft_strlen(var)) &&
// 			env[i][ft_strlen(var)] == '=')
// 		{
// 			to_add = ft_strjoin(var, "=", 'N');
// 			to_add = ft_strjoin(to_add, new_var, 'B');
// 			env[i] = to_add;
// 		}
// 		i++;
// 	}
// }

void ft_increase_shlvl(char **env)
{
	char	*new_shlvl;
	char	**tab_prompt;
	int		shlvl;

	if (!(tab_prompt = (char **)malloc(sizeof(char *) * 4)))
		return ;
	new_shlvl = ft_strdup(ft_getenv("SHLVL", env));
	shlvl = ft_atoi(new_shlvl);
	shlvl++;
	tab_prompt[0] = ft_strdup("setenv");
	tab_prompt[1] = ft_strdup("SHLVL");
	tab_prompt[2] = ft_itoa(shlvl);
	tab_prompt[3] = NULL;
	ft_setenv(tab_prompt, env);
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
	// ft_printtab(new_env);
	// ft_putendl("end of ft_create_env");
	return (new_env);
}
