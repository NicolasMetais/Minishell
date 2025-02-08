/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-08 11:50:12 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-08 11:50:12 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_commande
{
	char			**cmd;
	char			*path;
	char			*here_doc;
	int				in_fd[2];
	int				out_fd[2];

	struct s_commande *next;

}				t_cmd;    

typedef struct s_global
{
	int		nb_cmd;
	char	**path;
	t_cmd	*cmd;
}				t_glb;

void		free_split(char **split);
void		free_node(t_cmd *ctx);
void		freelist(t_cmd *cmd);
void		free_global(t_glb *glb);
void		free_split_init(char **split, int i)

t_boolean	get_fd(t_cmd *cmd, char **cmd_line_split);
t_boolean	get_outfd(t_cmd *cmd, char **cmd_split);
t_boolean	get_infd(t_cmd *cmd, char **cmd_split);

int			command_counter(char **line_split);
t_boolean	global_init(t_glb *glb, char *read_line, char **env);

char		*get_path(char **cmd_line_split, char **all_path);
char		**get_all_path(char **env);

char		**realloc_cmd(char **cmd, int supp);
t_boolean	realloc_fd_in(t_cmd *cmd, char **cmd_split, int i);
t_boolean	realloc_fd_out(t_cmd *cmd, char **cmd_split, int i);

#endif
