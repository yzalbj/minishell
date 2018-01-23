/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:35:45 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/23 14:49:04 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Builtin --> unsetenv [name ...]
*/

int		ft_changetab_forunsetenv(char *tab_prompt, char ***env, int i, int j)
{
	int		k;
	char	**new;

	if (!ft_strncmp(tab_prompt, (*env)[i], ft_strlen(tab_prompt)) &&
			(*env)[i][ft_strlen(tab_prompt)] == '=')
	{
		if (!(new = (char **)malloc(sizeof(char *) * (ft_tablen(*env)))))
			return (-1);
		k = 0;
		while ((*env)[j])
		{
			if (j != i)
			{
				new[k] = ft_strdup((*env)[j]);
				k++;
			}
			j++;
		}
		new[k] = NULL;
		ft_freetab(env);
		*env = new;
		return (0);
	}
	return (1);
}

int		ft_unsetenv(char **tab_prompt, char ***env)
{
	int		i;
	int		ret;

	if (!tab_prompt[1])
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (-1);
	}
	tab_prompt++;
	while (*tab_prompt)
	{
		i = 0;
		while ((*env)[i])
		{
			if (ft_strchr(*tab_prompt, '='))
				break ;
			if (!(ret = ft_changetab_forunsetenv(*tab_prompt, env, i, 0)))
				break ;
			if (ret == -1)
				ft_putendl_fd("unsetenv: error: Not enough memory.", 2);
			i++;
		}
		tab_prompt++;
	}
	return (1);
}

/*
**	Builtin --> setenv [name=value ...]
*/

void	ft_changetab_forsetenv(char **tab_prompt, char ***env, int i, int k)
{
	int		j;
	char	**new_env;

	j = 0;
	while (*env && (*env)[j])
	{
		if (!ft_strncmp(tab_prompt[i], (*env)[j], k) && (*env)[j][k] == '=')
		{
			ft_strdel(&(*env)[j]);
			(*env)[j] = ft_strdup(tab_prompt[i]);
			break ;
		}
		j++;
	}
	if (!(*env)[j])
	{
		new_env = ft_tabndup(*env, j + 1);
		new_env[j] = ft_strdup(tab_prompt[i]);
		ft_freetab(env);
		*env = new_env;
	}
}

int		ft_setenv(char **tab_prompt, char ***env)
{
	int		i;
	int		k;

	i = 1;
	if (!tab_prompt[1])
	{
		ft_printtab(*env);
		return (1);
	}
	while (tab_prompt[i])
	{
		k = 0;
		while (tab_prompt[i][k] && tab_prompt[i][k] != '=')
			k++;
		if (!tab_prompt[i][k])
		{
			ft_putstr_fd("error: ", 2);
			ft_putstr_fd(tab_prompt[i], 2);
			ft_putendl_fd(" must contain a \'=\'", 2);
			return (-1);
		}
		ft_changetab_forsetenv(tab_prompt, env, i, k);
		i++;
	}
	return (0);
}
