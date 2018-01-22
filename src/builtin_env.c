/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:54:19 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/22 15:19:50 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_shell *s, char ***env)
{
	int		i;
	char	**new_env;
	char	**new_var;
	pid_t	process;

	i = 1;
	if (!*env)
		return ;
	if (!s->tab_prompt[1])
		ft_printtab(*env);
	else if (s->tab_prompt[1])
	{
		if (!ft_strcmp(s->tab_prompt[1], "-i"))
		{
			i++;
			new_env = NULL;
			if (s->tab_prompt[i] && ft_strchr(s->tab_prompt[i], '='))
			{
				if (!(new_env = (char **)malloc(sizeof(char *) * 1)))
					return ;
				*new_env = NULL;
			}
			while (s->tab_prompt[i] && ft_strchr(s->tab_prompt[i], '='))
			{
				new_var = ft_strsplit(s->tab_prompt[i], '=');
				ft_createtab_for_setenv(new_var[0], new_var[1], 'N');
				ft_freetab(&new_var);
				ft_setenv(new_var, &new_env);
				i++;
			}
		}
		else
			new_env = ft_tabdup(s->env);
		process = fork();
		if (!process)
		{
			ft_exec(&s->tab_prompt[i], s->builtin, new_env);
			exit(0);
		}
		else
		{
			wait(0);
			s->tab_prompt = ft_tabdup(s->tab_prompt + i);
			ft_builtin(s, &new_env);
		}
	}
}

void ft_changetab_forunsetenv(char *tab_prompt, char ***env, int i)
{
	int		j;
	int		k;
	char	**new;

	while ((*env)[i])
	{
		if (ft_strchr(tab_prompt, '='))
			break ;
		if (!ft_strncmp(tab_prompt, (*env)[i], ft_strlen(tab_prompt)))
		{
			ft_putnbr(ft_tablen(*env));
			if (!(new = (char **)malloc(sizeof(char *) * (ft_tablen(*env)))))
				return ;
			j = 0;
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
			*env = new;
			break ;
		}
		i++;
	}
}

int		ft_unsetenv(char **tab_prompt, char ***env)
{
	int		i;
	// int		j;
	// int		k;
	// char	**new;

	if (!tab_prompt[1])
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (-1);
	}
	tab_prompt++;
	while (*tab_prompt)
	{
		i = 0;
		// UNSETENV MARCHE PAS AU PREMIER UNSETENV _ et MARCHE AU DEUXIEME
		// ON DIRAIT QUE QUAND JE CLONE LENV JE LE COPIE DE 1 DE TROP
		// cf --> tablen


		// while ((*env)[i])
		// {
		// 	if (ft_strchr(*tab_prompt, '='))
		// 		break ;
		// 	if (!ft_strncmp(*tab_prompt, (*env)[i], ft_strlen(*tab_prompt)))
		// 	{
		// 		if (!(new = (char **)malloc(sizeof(char *) * (ft_tablen(*env)))))
		// 			return (-1);
		// 		j = 0;
		// 		k = 0;
		// 		while ((*env)[j])
		// 		{
		// 			if (j != i)
		// 				new[k++] = ft_strdup((*env)[j]);
		// 			j++;
		// 		}
		// 		new[k] = NULL;
		// 		*env = new;
		// 		break ;
		// 	}
		// 	i++;
		// }
		ft_changetab_forunsetenv(*tab_prompt, env, i);
		tab_prompt++;
	}
	return (1);
}

/*
**	Builtin --> setenv [name=value] ...
*/

void ft_changetab_forsetenv(char **tab_prompt, char ***env, int i, int k)
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
			ft_putendl_fd("must contain a \'=\'", 2);
			return (-1);
		}
		ft_changetab_forsetenv(tab_prompt, env, i, k);
		i++;
	}
	return (0);
}
