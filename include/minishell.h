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
# include <math.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef enum s_boolean
{
	false,
	true,
}			t_boolean;

typedef struct s_pipe
{
	char		**cmd_tab;
	char		*tmp;
	char		*str;
	char		*fstr;
	int			c;
	int				i;
	int			end;
	t_boolean	valid;
	t_boolean	quote;

}				t_pipe_var;

t_boolean	is_redirection_char(char s);
t_boolean	is_redirection(char	*s);
char		**get_fd(t_cmd *cmd, char **cmd_line_split);
char		**get_outfd(t_cmd *cmd, char **cmd_split);
char		**get_infd(t_cmd *cmd, char **cmd_split);
char		**realloc_fd_in(t_cmd *cmd, char **cmd_split, int i);
char		**realloc_fd_out(t_cmd *cmd, char **cmd_split, int i);
t_glb		*global_init(char *read_line, char **env);
char		*remove_double_quote(char *line, int *end);
void		increment(t_pipe_var *ctx);
t_boolean	is_in_quote(char *str);
t_boolean 	quote_inside(char *str, int i);
t_boolean	 space_in_quote(char *str);


#endif