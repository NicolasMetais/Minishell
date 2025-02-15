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
	struct s_commande	*next;
}				t_cmd;

typedef struct s_global
{
	int		nb_cmd;
	char	**path;
	t_cmd	*cmd;
}				t_glb;

typedef	struct s_utils
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
}			t_utils;

typedef struct s_quote
{
	char	**tab;
	char	*tmp;
	int		end;
	char	*str;
}				t_quote;

void		free_split(char **split);
void		free_node(t_cmd *ctx);
void		freelist(t_cmd *cmd);
void		free_global(t_glb *glb);
void		free_split_init(char **split, int i);
int			command_counter(char **line_split);
char		*get_path(char **cmd_line_split, char **all_path);
char		**get_all_path(char **env);
char		**realloc_cmd(char **cmd, int supp);
int			open_file_in(char	*file);
int			open_file_out(char	*file, int i);
char		**get_cmd(char **cmd_line_split, char **all_path);
int			search_cmd(char **all_path, char **cmd);
char		**handle_heredoc(char **cmd_split, t_cmd *cmd, int i);
char		**handle_in_redirection(char **cmd_split, t_cmd *cmd, int i);
char		**get_quote(char *line_split);
char		**realloc_quote(char **tab, char *new);
int			check_backward(char	*line);
char		*nothing_backward_double(char *line);
char		*nothing_backward_simple(char *line);
char		*handle_simple_quote(char *line);
char		*handle_double_quote(char *line);
char		*remove_double_quote(char *line, int *end);
char		*remove_simple_quote(char *line, int *end);
char		*ft_strndup(char *line, int c);
char		*ft_strndup_bis(char *line, int c);
int			is_a_sep(char c);
char		*handle_quote(char *line);
char		*handle_remove(char *line, int *end);
char    	*handle_no_quote(char *line);
char		*remove_no_quote(char *line, int *end);
char		*realloc_line(char	*old, int c, int *end);

#endif
