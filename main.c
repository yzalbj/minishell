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

#include "./includes/minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_prompt	p;
	pid_t		process;
	char		*pwd;

	(void)argc;
	(void)argv;
	p.env = ft_create_env(env);
	p.builtin = create_builtin_tab();
	while (1)
	{
		pwd = ft_getenv("PWD", p.env);
		ft_putstr("\e[32m");
		if (pwd)
			ft_putstr(pwd);
		else
			ft_putchar('$');
		ft_putstr("\e[0m");
		ft_putstr(" > ");
		ft_strdel(&pwd);
		p.prompt = NULL;
		signal(SIGINT, ft_exit);
		get_next_line(0, &p.prompt);
		ft_manage_prompt(&p.tab_prompt, p.prompt, p.env);
		if (!p.tab_prompt[0])
			continue ;
		process = fork();
		if (!process)
		{
			ft_exec(&p, p.tab_prompt, p.env);
			return (0);
		}
		else
		{
			wait(0);
			ft_builtin(&p, &p.env);
		}
	}
	return (0);
}
