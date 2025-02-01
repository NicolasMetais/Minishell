/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/01 03:19:17 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"


# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <dirent.h>
#include <unistd.h>
# include <readline/history.h>

typedef struct s_core
{
	int				ac;
	char			**av;
	char			**env;
	unsigned int	dollars_qmark;
	char			*line;
}	t_core;

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

void	funny_stuff(void);
void	cd(t_core *core);
void	cmd_exec(t_core *core);
void	env_var(t_core *core);
void	exit_status_display(t_core *core);
void	signal_handler(void);
#endif