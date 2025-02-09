/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/28 06:11:54 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"

# include "parsing.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef enum s_boolean
{
	false,
	true,
}			t_boolean;

void		funny_stuff(void);

t_boolean	is_redirection(char	*s);
char		**get_fd(t_cmd *cmd, char **cmd_line_split);
char		**get_outfd(t_cmd *cmd, char **cmd_split);
char		**get_infd(t_cmd *cmd, char **cmd_split);
char		**realloc_fd_in(t_cmd *cmd, char **cmd_split, int i);
char		**realloc_fd_out(t_cmd *cmd, char **cmd_split, int i);
t_glb		*global_init(char *read_line, char **env);


#endif