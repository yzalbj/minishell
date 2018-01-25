/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 18:15:27 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/22 15:17:49 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_singleton_env(char **env)
{
	static char	**mem_env;

	if (env)
		mem_env = env;
	else
		return (mem_env);
	return (NULL);
}

void	ft_control_c(int sig)
{
	ft_putchar('\n');
	if (sig)
		ft_display_prompt(ft_singleton_env(NULL));
}
