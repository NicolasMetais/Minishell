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


# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

typedef struct s_commande
{
	char			**cmd;
	char			*path;
	int				in_fd[2];
	int				out_fd[2];

	struct s_command *next;

}				t_cmd;    

typedef struct s_global
{
	int		nb_cmd;
	char	**path;
	t_cmd	*cmd;
}				t_glb;

void	funny_stuff(void);

void	free_split(char **split);
void	free_node(t_cmd *ctx);

void	get_fd(t_cmd *cmd, char **cmd_line_split);
int		get_outfd(t_cmd *cmd, char **cmd_split);
int		get_infd(t_cmd *cmd, char **cmd_split);

t_boolean	is_redirection(char	*s);
int			command_counter(char **line_split)

#endif