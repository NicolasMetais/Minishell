/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:50:12 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/06 02:18:54 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "boolean.h"

typedef struct s_commande
{
	char				**args;
	char				**here_doc;
	int					in_fd[2];
	int					out_fd[2];
	int					args_nb;
	struct s_commande	*next;
}				t_cmd;

typedef struct s_global
{
	int			nb_cmd;
	char		**path;
	t_boolean	absolute_path;
	t_cmd		*cmd;
}				t_glb;

typedef struct s_free_var
{
	char	*str;
	char	*tmp;
	char	*word;

}			t_free_var;

typedef struct s_utils
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
}			t_utils;

typedef struct s_pignouf
{
	int		i;
	int		j;
	int		len;
	char	*new;
}				t_pignouf;

void		free_split(char **split);
void		free_node(t_cmd *ctx);
void		freelist(t_cmd *cmd);
void		free_global(t_glb *glb);
void		free_split_init(char **split, int i);
int			command_counter(char **line_split);
char		**get_all_path(char **env);
char		**realloc_cmd(char **cmd, int supp);
int			open_file_in(char *file);
int			open_file_out(char *file, int i);
char		**handle_heredoc(char **cmd_split, t_cmd *cmd, int i);
char		**handle_in_redirection(char **cmd_split, t_cmd *cmd, int i);
char		**get_quote_dup(char *line_split);
char		**realloc_add_to_tab(char **tab, char *new);
char		*ft_strndup(char *line, int c);
char		*ft_strdup_end(char *str, int c);
int			is_a_sep(char c);
char		*realloc_line(char *old, int c, int *end);
char		**get_pipe(char *line);
char		*ft_strnjoin(char const *s1, char const *s2, int c);
char		*ft_strjoin_custom(char const *s1, char const *s2);
char		*ft_pignouf(char *line);

#endif
