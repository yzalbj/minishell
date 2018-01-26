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

void	ft_checkpwd(char ***env)
{
	char		*tmp;
	char		**reset_pwd;
	struct stat	stat_tmp;

	if (!(tmp = ft_getenv("PWD", *env)) || !tmp[0] || access(tmp, F_OK) ||
		(!lstat(tmp, &stat_tmp) && ((stat_tmp.st_mode & S_IFDIR) != S_IFDIR &&
			(stat_tmp.st_mode & S_IFLNK) != S_IFLNK)) || !ft_strcmp(tmp, ".") ||
			!ft_strcmp(tmp, ".."))
	{
		reset_pwd = ft_createtab_for_setenv("PWD", getcwd(NULL, 0), 'R');
		ft_setenv(reset_pwd, env);
		ft_freetab(&reset_pwd);
	}
	if (tmp)
		ft_strdel(&tmp);
}

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
	ft_freetab(&(s->tab_prompt));
	ft_strdel(&(s->prompt));
}

int		main(int argc, char **argv, char **env)
{
	t_shell		s;

	s.env = ft_create_env(env);
	s.builtin = create_builtin_tab();
	s.pwd = ft_getenv("PWD", s.env);
	ft_singleton_sh(&s);
	while (argc && argv)
	{
		ft_checkpwd(&s.env);
		ft_manage_prompt(&s);
		if (!s.tab_prompt || !s.tab_prompt[0])
		{
			ft_strdel(&(s.prompt));
			ft_freetab(&(s.tab_prompt));
			continue ;
		}
		ft_process(&s);
	}
	return (0);
}
