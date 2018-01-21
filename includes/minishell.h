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
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>

// typedef struct		s_opt
// {
// 	int				L;
// 	int				P;
// }					t_opt;

typedef	struct			s_prompt
{
	char				c;
	char				*str;
}						t_prompt;

typedef struct			s_shell
{
	// char			*path_env;
	char				**builtin;
	char				**env;
	char				*prompt;
	char				**tab_prompt;
}						t_shell;

void ft_control_c(int sig);
/*
**	BUILTIN_ECHO.C
*/

int		ft_echo(t_shell *s, char **env);

/*
**	PROMPT.C
*/

char		*create_strprompt(t_list *begin);
char		*ft_read_prompt(char **env);
void		ft_display_prompt(char **env);
void		ft_manage_prompt(char ***tab_prompt, char *prompt, char **env);

/*
**	BUILTIN.C
*/


char	**create_builtin_tab(void);

/*
**	BUILTIN_CD.C
*/
char	*ft_concatpath(char *path, char **env, char *to_add);
char	*ft_shortpath(char *path, int i, int j);
int	ft_cd(t_shell *s, char ***env);
/*
**	BUILTIN_ENV.C
*/

void ft_env(t_shell *s, char ***env);
int		ft_setenv(char **tab_prompt, char ***env);
int		ft_unsetenv(char **tab_prompt, char ***env);
/*
**	ENV.C
*/

char	**ft_create_env(char **env);
void ft_increase_shlvl(char **env);
char	**ft_createtab_for_setenv(char *name, char *value, char f);
char	*ft_getenv(char *var, char **env);
void ft_update_pwd(char *new_pwd, char ***env);

/*
**	EXEC.C
*/

void ft_exec( char **tab_prompt, char **env);

void ft_exit(t_shell *s, int ex);
int ft_builtin(t_shell *s, char ***env);
#endif
