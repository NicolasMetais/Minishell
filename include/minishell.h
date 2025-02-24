/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/23 15:12:40 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"
# define WHITE "\e[0;37m"

# include "libft.h"

# include <stdio.h>
# include <math.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>

extern unsigned int exit_code;

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

# include "cmd.h"
# include "errors.h"

typedef struct s_pipe
{
	char		**cmd_tab;
	char		*tmp;
	char		*str;
	char		*fstr;
	int			c;
	int			i;
	int			end;
	t_boolean	valid;
	t_boolean	quote;

}				t_pipe_var;

typedef struct s_env
{
	char			*name;
	char			*var;
	struct s_env	*next;
}		t_env;

typedef struct s_core
{
	int				ac;
	char			**av;
	char			*pwd;
	char			*prompt;
	char			*line;
	char			**new_line;
	char			**temp_path;
	char			**env_dup;
	t_env			*env;
	t_env			*mark;
}	t_core;

void		funny_stuff(void);

//UTILS
t_boolean	update_env_dup(t_core *core);
char		*ft_get_env(t_env *env, char *name);
t_env		*rotate_env(t_core *core, char *var_name);
int			ft_strcmp(char *s1, char *s2);
int			get_env_size(t_env	*env);
t_boolean	env_exist(t_core *core, char *var);

//ENV VARIABLE CONVERSIONS
t_boolean	setup_var(t_core *core);
char		*delete_var(char *tocut, int start, int end);
char		*write_var(char *code, char *tocut, int j, int size);

//ENV VAR INIT
t_boolean	duplicate_env(t_core *core, char **todup);
t_env		*new_env(char *todup);
t_env		*lstlast_env(t_env *lst);

//SIGNALS
void		signal_update(void);
void		signal_reset(void);

//FREE
void		emergency_free_tab(char **tab, int i);
void		emergency_free_env_var(t_env *env);
void		free_env(t_core *core);
void		free_tab(char **tab);

//KILL
void		kill_program(t_core *core);

#endif