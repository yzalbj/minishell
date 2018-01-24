/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:24:17 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/23 17:24:22 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*
**	WHEN TO ADD IS NULL, WE ADD THE PWD TO PATH
*/

char	*ft_concatpath(char *path, char **env, char *to_add, char free_path)
{
	char	*tmp;
	int		i;

	if (!to_add)
		tmp = ft_getenv("PWD", env);
	else
		tmp = ft_strdup(to_add);
	i = 0;
	while (tmp && tmp[i + 1])
		i++;
	if (tmp && tmp[i] != '/')
		tmp = ft_strjoin(tmp, "/", 'L');
	if (free_path)
		path = ft_strjoin(tmp, path, 'B');
	else
		path = ft_strjoin(tmp, path, 'L');
	return (path);
}

void	ft_shortpath(char **path, int i, int j)
{
	while ((*path)[i])
	{
		if (!ft_strncmp(&(*path)[i], "/.", 2) &&
			((*path)[i + 2] == '/' || !(*path)[i + 2]))
		{
			(*path) = ft_strshort((*path), i, 2, 1);
			i = 0;
		}
		else if (!ft_strncmp(&(*path)[i], "/..", 3) &&
			((*path)[i + 3] == '/' || !(*path)[i + 3]))
		{
			j = i > 0 ? i - 1 : 0;
			while (j && (*path)[j] != '/')
				j--;
			if (!(*path)[i + 3])
				(*path) = ft_strshort((*path), j + 1, i - j + 2, 1);
			else
				(*path) = ft_strshort((*path), j + 1, i - j + 3, 1);
			i = 0;
		}
		else if ((*path)[i] == '/' && (*path)[i + 1] == '/')
			(*path) = ft_strshort((*path), i, 1, 1);
		else
			i++;
	}
}
