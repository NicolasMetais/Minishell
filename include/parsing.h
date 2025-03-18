/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:50:12 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 02:07:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum s_type_red
{
	double_,
	simple,
}			t_type_red;

typedef struct s_db_et_simp
{
	int			db;
	int			simp;
}				t_blue;

typedef struct s_file
{
	t_type_red		type;
	t_boolean		complete;
	char			*file;
	struct s_file	*next;
}				t_file;

typedef struct s_commande
{
	char				**args;
	char				**here_doc;
	t_boolean			is_a_directory;
	t_file				*in;
	t_file				*out;
	int					error;
	int					args_nb;
	struct s_commande	*next;
}				t_cmd;

typedef struct s_global
{
	int			nb_cmd;
	t_boolean	absolute_path;
	t_cmd		*cmd;
	t_file		*all_in;
	t_file		*all_out;
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

typedef struct s_realloc_get_bool
{
	int	i;
	int	len;
	int	*new;
}				t_r_get_bool;

typedef struct s_pignouf
{
	int		i;
	int		j;
	int		len;
	char	*new;
}				t_pignouf;

typedef struct s_get_line_index
{
	int	j;
	int	i;
	int	tab_len;
}				t_index;

typedef struct s_get_file_handle_un_word_var
{
	char	*tmp;
	char	c;
	int		i;
	int		j;
}				t_un_word_var;

void		free_split(char **split);
void		free_node(t_cmd *ctx);
void		freelist(t_cmd *cmd);
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
char		*ft_strnjoin(char const *s1, char const *s2, int c);
char		*ft_strjoin_custom(char const *s1, char const *s2);
char		*ft_pignouf_prime(char *line);
int			bool_len(int *bool);
char		*realloc_str_file(char *str, int i, int j);

#endif
