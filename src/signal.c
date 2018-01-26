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

t_shell	*ft_singleton_sh(t_shell *s)
{
	static t_shell	*mem_sh;

	if (s)
		mem_sh = s;
	else
		return (mem_sh);
	return (NULL);
}

void	ft_control_c(int sig)
{
	ft_putchar('\n');
	if (sig)
		ft_display_prompt();
}
