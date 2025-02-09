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

typedef struct s_commande
{
	char				**cmd;
	char				*path;
	char				*here_doc;
	int					in_fd[2];
	int					out_fd[2];

	struct s_commande 	*next;

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
void		free_split_init(char **split, int i);
int			command_counter(char **line_split);
char		*get_path(char **cmd_line_split, char **all_path);
char		**get_all_path(char **env);
char		**realloc_cmd(char **cmd, int supp);
int			open_file(char	*file);
char		**get_cmd(char **cmd_line_split, char **all_path);
int			search_cmd(char **all_path, char **cmd);




#endif
