/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:54:19 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/10 14:54:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// on est en trai de faire l'env, check si exec marche bien quand l'env est null, si on envoit bien le tab_prompt
// qd ya juste -i, jetais en train d'envoyer un tab ou le permier elem = null quad je fais juste env -i, ale a+

void ft_env(t_prompt *p)
{
	int		i;
	char	**new_env;
	char	**new_var;
	pid_t	process;

	i = 1;
	if (!p->tab_prompt[1])
		ft_printtab(p->env);
	else if (p->tab_prompt[1])
	{
		if (!ft_strcmp(p->tab_prompt[1], "-i"))
		{
			i++;
			new_env = ft_create_env(NULL);
			while (p->tab_prompt[i] && ft_strchr(p->tab_prompt[i], '='))
			{
				p->tab_prompt[i] = ft_strjoin("setenv=", p->tab_prompt[i], 'R');
				new_var = ft_strsplit(p->tab_prompt[i], '=');
				ft_setenv(new_var, &new_env);
				i++;
			}
		}
		else
			new_env = ft_tabdup(p->env);
		process = fork();
		if (!process)
		{
			ft_exec(p, &p->tab_prompt[i], new_env);
			exit(0);
		}
		else
			wait(0);
	}
}

int		ft_unsetenv(char **tab_prompt, char ***env)
{
	int		i;
		int		j;
		int		k;
		char	**new;

		if (!tab_prompt[1])
		{
			ft_putendl("unsetenv: Too few arguments.");
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
				if (!ft_strncmp(*tab_prompt, (*env)[i], ft_strlen(*tab_prompt)))
				{
					if (!(new = (char **)malloc(sizeof(char *) * (ft_tablen(*env)))))
						return (-1);
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
					i = 0;
				}
				i++;
			}
			tab_prompt++;
		}
		return (1);
}

int		ft_setenv(char **tab_prompt, char ***env)
{
	int		i;
	char	**new_env;
	char	*to_add;

	i = 0;
	if (!tab_prompt[1])
	{
		ft_printtab(*env);
		return (1);
	}
	if (tab_prompt[3])
	{
		ft_putendl_fd("setenv: usage: setenv [name] [value].", 2);
		return (-1);
	}
	if (ft_strchr(tab_prompt[1], '='))
	{
		ft_putendl_fd("error: [name] must not contain \'=\'.", 2);
		return (-1);
	}
	to_add = ft_strjoin(tab_prompt[1], "=", 'N');
	if (tab_prompt[2])
		to_add = ft_strjoin(to_add, tab_prompt[2], 'L');
	while ((*env)[i])
	{
		if (!ft_strncmp(tab_prompt[1], (*env)[i], ft_strlen(tab_prompt[1])) &&
			(*env)[i][ft_strlen(tab_prompt[1])] == '=')
		{
			(*env)[i] = to_add;
			return (0);
		}
		i++;
	}
	new_env = ft_tabndup(*env, i + 1);
	new_env[i] = to_add;
	*env = new_env;
	return (0);
}
