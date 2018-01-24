/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:48:52 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/23 17:47:06 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef	struct	s_prompt
{
	char		c;
	char		*str;
}				t_prompt;

typedef struct	s_shell
{
	char		**builtin;
	char		**env;
	char		*prompt;
	char		**tab_prompt;
}				t_shell;

/*
**	signal.c
*/

void			ft_control_c(int sig);

/*
**	builtin_echo.c
*/

int				ft_echo(t_shell *s);

/*
**	prompt.c
*/

void			ft_display_prompt(char **env);
void			ft_manage_prompt(t_shell *s);

/*
**	builtin.c
*/

int				ft_builtin(t_shell *s, char ***env);
char			**create_builtin_tab(void);

/*
**	builtin_cd_utils.c
*/

char			*ft_concatpath(char *path, char **env,
					char *to_add, char free_path);
void			ft_shortpath(char **path, int i, int j);
char			ft_isoptp(char **tab_prompt, int *i);

/*
**	builtin_cd.c
*/

void			ft_cd(t_shell *s, char ***env);

/*
**	builtin_setenv.c
*/

int				ft_setenv(char **tab_prompt, char ***env);
int				ft_unsetenv(char **tab_prompt, char ***env);

/*
**	builtin_env.c
*/

void			ft_env(t_shell *s, char ***env);

/*
**	env.c
*/

char			**ft_create_env(char **env);
void			ft_increase_shlvl(char ***env);
char			**ft_createtab_for_setenv(char *name, char *value, char f);
char			*ft_getenv(char *var, char **env);
void			ft_update_pwd(char *new_pwd, char ***env);

/*
**	exec.c
*/

void			ft_exec(char **tab_prompt, char **builtin, char **env);
void			ft_exit(t_shell *s, int ex);
#endif
