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
	// ft_increase_shlvl(p.env);
	while (1)
	{
		pwd = ft_getenv("PWD", p.env);
		ft_putstr(pwd);
		ft_putstr(" > ");
		ft_strdel(&pwd);

		p.prompt = NULL;
		get_next_line(0, &p.prompt);
		p.tab_prompt = ft_strsplit(p.prompt, ' ');
		// ft_printtab(p.tab_prompt);
		int		i = 0;
		while (p.tab_prompt[i])
		{
			p.tab_prompt[i] = ft_strtrim(p.tab_prompt[i]);
			i++;
		}
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
			ft_builtin(&p);
		}
	}
	return (0);
}
