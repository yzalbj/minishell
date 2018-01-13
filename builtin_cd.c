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

	while (!ft_strcmp(tab_prompt[*i], "-L") || !ft_strcmp(tab_prompt[*i], "-P"))
	{
		if (!ft_strcmp(tab_prompt[*i], "-L"))
		{
			opt->P = 0;
			opt->L = 1;
		}
		else
		{
			opt->L = 0;
			opt->P = 1;
		}
		*i++;
	}
	if (opt->L != 1)
		opt->L = 0;
	if (opt->P != 1)
		opt->P = 0;
	return (opt);
}

int	ft_cd(t_prompt *p)
{
	char	*path;
	t_opt	opt;
	int		i;

	opt = ft_create_option(p->tab_prompt, &i);
	if (p->tab_prompt[2])
}
