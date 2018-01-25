/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:41:30 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/25 16:06:15 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_process(t_shell *s)
{
	pid_t		process;

	process = fork();
	if (!process)
		ft_exec(s->tab_prompt, s->builtin, s->env);
	else
	{
		wait(0);
		ft_builtin(s, &s->env);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_shell		s;

	s.env = ft_create_env(env);
	s.builtin = create_builtin_tab();
	while (argc && argv)
	{
		ft_manage_prompt(&s);
		if (!s.tab_prompt || !s.tab_prompt[0])
		{
			ft_strdel(&(s.prompt));
			ft_freetab(&(s.tab_prompt));
			continue ;
		}
		ft_process(&s);
		ft_strdel(&(s.prompt));
		ft_freetab(&(s.tab_prompt));
	}
	return (0);
}
