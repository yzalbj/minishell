/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:41:30 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/09 16:41:59 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_shell		s;
	int			i;
	pid_t		process;

	(void)argc;
	(void)argv;
	s.env = ft_create_env(env);
	s.builtin = create_builtin_tab();
	while (1)
	{
		ft_display_prompt(s.env);
		s.prompt = NULL;
		signal(SIGINT, &ft_control_c);
		 if (!get_next_line(0, &s.prompt))
		 	ft_exit(&s, 0);
		ft_manage_prompt(&s.tab_prompt, s.prompt, s.env);
		if (!s.tab_prompt || !s.tab_prompt[0])
		{
			// ft_putchar('\n');
			continue ;
		}
		process = fork();
		if (!process)
		{
			i = 0;
			while (s.builtin[i])
			{
				if (!ft_strcmp(s.builtin[i], s.tab_prompt[0]))
					return (0);
				i++;
			}
			ft_exec(s.tab_prompt, s.env);
			return (0);
		}
		else
		{
			wait(0);
			ft_builtin(&s, &s.env);
		}
		ft_strdel(&(s.prompt));
		ft_freetab(&(s.tab_prompt));
	}
	return (0);
}
