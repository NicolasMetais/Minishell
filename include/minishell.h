/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/05 07:03:00 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"
# define WHITE "\e[0;37m"

# include "libft.h"

# include <stdio.h>
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

extern unsigned int g_dollar_qmark;

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

# include "cmd.h"

typedef struct s_env
{
	char			*name;
	char			*env;
	struct s_env	*next;
}		t_env;

typedef struct s_core
{
	int				ac;
	char			**av;
	char			*pwd;
	char			*prompt;
	char			*line;
	char			**temp_path;
	char			**env_dup;
	t_env			*env;
}	t_core;

void		funny_stuff(void);

//UTILS
char		*ft_get_env(t_env *env, char *name);
t_env		*rotate_env(t_core *core, char *var_name);

//ENV VAR INIT
void		duplicate_env(t_core *core, char **todup);

//SIGNALS
void		signal_handler(void);

#endif