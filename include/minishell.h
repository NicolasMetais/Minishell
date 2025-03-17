/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 21:01:18 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define LIGHT_BLUE "\033[38;2;100;149;237m"
# define WHITE "\e[0;37m"

//HEADERS
# include "boolean.h"
# include "parsing.h"
# include "exec.h"
# include "builtin.h"
# include "errors.h"
//LIBFT
# include "libft.h"
//C LIBS
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_redirection
{
	t_type_red				type;
	t_boolean				valid;
	t_boolean				error;
	struct s_redirection	*next;
}				t_red;

typedef struct s_tk_dollar
{
	t_boolean			valid;
	struct s_tk_dollar	*next;
}				t_tk_dollar;

typedef struct s_expand_var
{
	int			error;
	char		*new_line;
	char		*tmp;
	int			i;
	t_tk_dollar	*tmp_d;
	t_tk_dollar	*dollar;
}				t_expand_var;

typedef struct s_pipe_token
{
	t_boolean				valid;
	struct s_pipe_token		*next;
}				t_pipe_token;

typedef struct s_get_red_bool
{
	t_red		error;
	char		c;
	t_boolean	quote;
	char		*word;
	char		*tmp;
}				t_bool_red;

typedef struct s_get_tk_bool
{
	char		c_db;
	char		c_simp;
	int			k;
	char		*line;
	t_boolean	quote;
	t_tk_dollar	*tmp;
}				t_get_dollar_bool;

typedef struct s_get_pipe_bool
{
	char		c;
	t_boolean	quote;
	char		*word;
	char		*tmp;
}				t_bool_pipe;

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

typedef struct s_env
{
	char			*name;
	char			*var;
	struct s_env	*next;
}		t_env;

typedef struct s_core
{
	int				ac;
	int				nb_dollars;
	char			**av;
	char			*pwd;
	char			*prompt;
	char			*line;
	char			**new_line;
	char			*path;
	char			**splitted_path;
	char			**env_dup;
	int				exit_code;
	int				errorno;
	int				save;
	int				save1;
	t_glb			*glb;
	t_env			*env;
	t_env			*mark;
}	t_core;

//UTILS
t_boolean		update_env_dup(t_core *core);
char			*ft_get_env(t_env *env, char *name);
t_env			*rotate_env(t_core *core, char *var_name);
int				ft_strcmp(char *s1, char *s2);
int				get_env_size(t_env	*env);
t_boolean		env_exist(t_core *core, char *var);
long long		ft_atol(const char *nptr);
//MAIN UTILS
void			exit_program(t_core *core);
t_boolean		main_setup(t_core *core, t_glb **global);
t_boolean		restore_stdio(t_core *core);

//ENV VARIABLE CONVERSIONS
char			*delete_var(char *tocut, int start, int end);
char			*write_var(char *code, char *tocut, int j, int size);
void			rewrite_line(t_core *core, int arg_nb, int count);

//NEW EXPANSION DE VAR
char			*expansion_var(t_core *core);
int				*is_dollar(t_core *core, int *pos);
char			*dynamic_copy(char *old, char c);
void			init_var_expand(t_expand_var *ctx, t_core *core);
void			get_variable_incr(int *i, t_core *core);


//ENV VAR INIT
t_boolean		duplicate_env(t_core *core, char **todup);
t_env			*new_env(char *todup);
t_env			*lstlast_env(t_env *lst);
t_boolean		create_empty_env(t_core *core);
void 			free_tk_dollar(t_tk_dollar *dollar);


//SIGNALS
void			signal_update(void);
void			signal_reset(void);
void			setup_signal(void);

//FREE
void			emergency_free_tab(char **tab, int i);
void			emergency_free_env_var(t_env *env);
void			free_env(t_core *core);
void			free_tab(char **tab);
void			free_loop(t_glb *global, t_core *core);

//KILL
void			kill_program(t_core *core);

// HANDLE PIPE IN PARSINGt_file	*get_all_out(t_cmd *cmd)

void			handle_pipe(t_pipe_var *ctx);
void			handle_pipe_realloc_line_and_tab(t_pipe_var *ctx, char **tmp);
void			handle_pipe_get_cmd(t_pipe_var *ctx);
char			**get_pipe(char *line);
t_boolean		pipe_valid(char *line);

// STRUCT INIT PARSING

void			pipe_var_init(t_pipe_var *ctx, char *line);
void			quote_var_init(t_pipe_var *ctx, char *line);
void			get_word_init(t_quote *ctx, char *str, int j);

t_boolean		is_redirection_char(char s);
t_boolean		is_redirection(char	*s);
char			**get_fd(t_cmd *cmd, char **cmd_split, t_red *tab_red);
char			**get_outfd(t_cmd *cmd, char **cmd_split);
char			**get_infd(t_cmd *cmd, char **cmd_split);
char			**realloc_fd_in(t_cmd *cmd, char **cmd_split, int i);
char			**realloc_fd_out(t_cmd *cmd, char **cmd_split, int i);
t_glb			*global_init(t_core *core);
char			*remove_double_quote(char *line, int *end);
void			increment(t_pipe_var *ctx);
t_boolean		is_in_quote(char *str);
t_boolean		quote_inside(char *str, int i);
t_boolean		space_in_quote(char *str);
t_boolean		is_empty(char *str);

void			free_var_init(t_quote *ctx, t_free_var *f);
void			get_word_increment(t_quote	*ctx);

void			realloc_line_failed(t_quote *ctx, t_free_var *f);
void			join_custom_failed(t_quote *ctx, t_free_var *f);
void			ndup_failed(t_quote *ctx, t_free_var *f);
void			quote_or_not_free(t_quote *ctx, t_free_var *f);

void			add_back(t_cmd *head, t_cmd *new);
void			quote_or_not(t_quote *ctx);
void			handle_inside_quote(t_quote *ctx);
void			realloc_line_in_quote(t_quote *ctx, t_free_var *f);
void			get_word_in_quote(t_quote *ctx, t_free_var *f);
void			no_quote(t_quote *ctx, t_free_var *f);
void			get_word_init(t_quote *ctx, char *str, int j);
void			quote_var_init(t_pipe_var *ctx, char *line);
void			cmd_tab_handle_quote_failed(char **tmp, t_pipe_var *ctx);
void			realloc_line_handle_quote_failed(t_pipe_var *ctx);
void			get_word_failed(t_pipe_var *ctx);
void			reset_handle_quote(t_pipe_var *ctx);
void			quote_or_not_free_2(t_quote *ctx, t_free_var *f);
t_boolean		is_double(char *word);
void			init_bool_red(t_bool_red *ctx, char *word);
void			turn_true_get_bool(t_bool_red *ctx);
t_red			*get_tk_red(char *line, int *error);
char			*get_word(char *str, int j);
void			turn_false_get_bool(t_bool_red *ctx);
char			*get_one_line_of_cmd_split(char **cmd_split);
void			free_list_fd(t_file *cmd);
void			free_fd(t_file *in, t_file *out);
void			free_end_tab(char **cmd_tab, int i);
void			free_tab_red(t_red *cmd);
void			get_file_index_init(t_index *index, char **cmd_tab);
t_pipe_token	*get_tk_pipe(char *line, int *error);
void			set_new_tk_dollar_as_valid(t_tk_dollar *new, t_get_dollar_bool ctx);

void			get_file_increment(t_index *index, char **cmd_tab,
					t_red **tab_red);
t_boolean		get_file_incr_false(t_index *index, char **cmd_tab,
					t_red **tab_red);

char			*realloc_word_red_at_end(char *str, t_red *red_tab, int i);
char			*get_one_line_of_cmd_split(char **cmd_split);

// SEARCH FILE IN CHAR*
char			*handle_file_word_deux(char c, t_cmd *cmd, char *str,
					t_red **tab_red);
char			*handle_cmd_file_word_un(t_cmd *cmd, char *str,
					t_red **tab_red);

// CREATE FILES LIST IN CMD
void			add_file_to_cmd(char *file, char c, t_cmd *cmd, t_red *tab_red);
t_file			*create_file(char *file, t_file *list, t_type_red type,
					int complete);
t_file			*add_to_file_list(t_file *lst, t_file *new);
t_file			*get_all_out(t_cmd *cmd);
t_file			*get_all_in(t_cmd *cmd);

// EXTRACT FILES FROM CHAR**
char			**extract_file(t_cmd *cmd, char **cmd_tab, t_red **tab_red,
					t_index *index);
char			**three_token_in_two_word(char **cmd_tab, t_index *index,
					t_red **tab_red, t_cmd *cmd);
char			**two_token_in_one_word(char **cmd_tab, t_index *index,
					t_red **tab_red, t_cmd *cmd);
char			**simple_token(char **cmd_tab, t_index *index, t_red **tab_red,
					t_cmd *cmd);

// DOLLAR SIGN

void		get_bool_dollar_turn_false(t_get_dollar_bool *ctx);
void		get_bool_dollar_turn_true(t_get_dollar_bool *ctx);
void		init_get_dollar_bool(t_get_dollar_bool *ctx, char *str);
t_tk_dollar	*get_tk_dollar(char *line, int *error);


// HANDLE TOKEN ERROR

t_boolean		handle_token_error(char *readline, int *error);
t_boolean		token_error(t_pipe_token *pipe, t_red *red, char *str);
void			turn_true_pipe_bool(t_bool_pipe *ctx);
void			turn_false_pipe_bool(t_bool_pipe *ctx);

void			init_var_token_error(t_bool_pipe *var, char *str);
void			turn_false_tok_error(t_bool_pipe *var);
void			turn_true_tok_error(t_bool_pipe *var);
t_boolean		is_red_error(t_pipe_token *pipe, t_red **red, t_bool_pipe *ctx);
void			free_pipe_tk(t_pipe_token *tk);
t_boolean		redirection_error(t_pipe_token *pipe, t_red **red, char *str);
void			turn_pipe_bool(t_bool_pipe *ctx);
void			turn_bool_red(t_bool_red *ctx);
void			turn_token_error(t_bool_pipe *var);
t_boolean		quote_error(char *str);


#endif