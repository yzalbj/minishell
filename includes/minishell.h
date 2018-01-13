/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:48:52 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/09 16:49:24 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct		s_opt
{
	int				L;
	int				P;
}					t_opt;

typedef struct		s_prompt
{
	// char			*path_env;
	char			**builtin;
	char			**env;
	char			*prompt;
	char			**tab_prompt;
}					t_prompt;

/*
**	BUILTIN.C
*/

char	**create_builtin_tab(void);

/*
**	BUILTIN.C
*/

void ft_env(t_prompt *p);
int		ft_setenv(char **tab_prompt, char ***env);
int		ft_unsetenv(char **tab_prompt, char ***env);
/*
**	ENV.C
*/

char	**ft_create_env(char **env);
void ft_increase_shlvl(char **env);
char	*ft_getenv(char *var, char **env);

/*
**	EXEC.C
*/

void ft_exec(t_prompt *p, char **tab_prompt, char **env);
int ft_builtin(t_prompt *p);
#endif
