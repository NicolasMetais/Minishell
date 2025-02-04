/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/04 04:50:03 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"


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

# define WHITE "\e[0;37m"

typedef struct s_core
{
	int				ac;
	char			**av;
	char			**env;
	char			*pwd;
	char			*prompt;
	char			*line;
	char			**temp_path;
}	t_core;

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

void		funny_stuff(void);
void		cd(t_core *core);
void		cmd_exec(t_core *core);
void		env_var(t_core *core);
void		exit_status_display(t_core *core);
void		signal_handler(void);

t_boolean	builtin(t_core *core);

void	cd_parsing(t_core *core);
#endif