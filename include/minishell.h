/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 17:54:18 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"
# define WHITE "\e[0;37m"

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>

extern unsigned int exit_code;

typedef enum s_boolean
{
	false,
	true,
}			t_boolean;

# include "parsing.h"

typedef struct s_redirection
{
	t_type_red				type;
	t_boolean				valid;
	t_boolean				error;
	struct s_redirection	*next;
}				t_red;

typedef	struct s_get_red_bool
{
	t_red		error;
	char		c;
	t_boolean	quote;
	char		*word;
	char 		*tmp;
}				t_bool_red;

typedef struct s_pipe
{
	char		**cmd_tab;
	char		*tmp;
	char		*str;
	char		*fstr;
	int			c;
	int			i;
	int			end;
	t_boolean	valid;
	t_boolean	quote;

}				t_pipe_var;

typedef struct s_quote
{
	t_boolean	quote;
	t_boolean	no_quote;
	char		*word;
	char		*str;
	char		*fstr;
	char		*tmp;
	char		*first;
	int			i;
	int			k;
	char		c;
}				t_quote;

# include "cmd.h"
# include "errors.h"

typedef struct s_env
{
	char			*name;
	char			*var;
	struct s_env	*next;
}		t_env;

typedef struct s_core
{
	int				ac;
	char			**av;
	char			*pwd;
	char			*prompt;
	char			*line;
	char			**new_line;
	char			**temp_path;
	char			**env_dup;
	t_env			*env;
	t_env			*mark;
}	t_core;

void		funny_stuff(void);

//UTILS
t_boolean	update_env_dup(t_core *core);
char		*ft_get_env(t_env *env, char *name);
t_env		*rotate_env(t_core *core, char *var_name);
int			ft_strcmp(char *s1, char *s2);
int			get_env_size(t_env	*env);
t_boolean	env_exist(t_core *core, char *var);
long long	ft_atol(const char *nptr);

//ENV VARIABLE CONVERSIONS
t_boolean	setup_var(t_core *core);
char		*delete_var(char *tocut, int start, int end);
char		*write_var(char *code, char *tocut, int j, int size);

//ENV VAR INIT
t_boolean	duplicate_env(t_core *core, char **todup);
t_env		*new_env(char *todup);
t_env		*lstlast_env(t_env *lst);
t_boolean	create_empty_env(t_core *core);

//SIGNALS
void		signal_update(void);
void		signal_reset(void);

//FREE
void		emergency_free_tab(char **tab, int i);
void		emergency_free_env_var(t_env *env);
void		free_env(t_core *core);
void		free_tab(char **tab);

//KILL
void		kill_program(t_core *core);


// HANDLE PIPE IN PARSING
void		handle_pipe(t_pipe_var *ctx);
void		handle_pipe_realloc_line_and_tab(t_pipe_var *ctx, char **tmp);
void		handle_pipe_get_cmd(t_pipe_var *ctx);
char		**get_pipe(char *line);
t_boolean	pipe_valid(char *line);

// STRUCT INIT PARSING

void	pipe_var_init(t_pipe_var *ctx, char *line);
void	quote_var_init(t_pipe_var *ctx, char *line);
void	get_word_init(t_quote *ctx, char *str, int j);

t_boolean	is_redirection_char(char s);
t_boolean	is_redirection(char	*s);
char		**get_fd(t_cmd *cmd, char **cmd_split, t_red *tab_red);
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
t_boolean	is_empty(char *str);

void		free_var_init(t_quote *ctx, t_free_var *f);
void		get_word_increment(t_quote	*ctx);

void		realloc_line_failed(t_quote *ctx, t_free_var *f);
void		join_custom_failed(t_quote *ctx, t_free_var *f);
void		ndup_failed(t_quote *ctx, t_free_var *f);
void		quote_or_not_free(t_quote *ctx, t_free_var *f);

void		quote_or_not(t_quote *ctx);
void		handle_inside_quote(t_quote *ctx);
void		realloc_line_in_quote(t_quote *ctx, t_free_var *f);
void		get_word_in_quote(t_quote *ctx, t_free_var *f);
void		no_quote(t_quote *ctx, t_free_var *f);
void		get_word_init(t_quote *ctx, char *str, int j);
void		quote_var_init(t_pipe_var *ctx, char *line);
void		cmd_tab_handle_quote_failed(char **tmp, t_pipe_var *ctx);
void		realloc_line_handle_quote_failed(t_pipe_var *ctx);
void		get_word_failed(t_pipe_var *ctx);
void		reset_handle_quote(t_pipe_var *ctx);
void		quote_or_not_free_2(t_quote *ctx, t_free_var *f);
t_boolean	unexpected_token_red(char *cmd_one_line, t_red *tab_red);
t_boolean	is_double(char *word);
void		init_bool_red(t_bool_red *ctx, char *word);
void		turn_true_get_bool(t_bool_red *ctx);
t_red		*get_tk_red(char *line);
char		*get_word(char *str, int j);
void		turn_false_get_bool(t_bool_red *ctx);
char		*get_one_line_of_cmd_split(char **cmd_split);
void		free_list_fd(t_file *cmd);
void    	free_fd(t_file *in, t_file *out);
void 		free_end_tab(char **cmd_tab, int i);
void		free_tab_red(t_red *cmd);

#endif