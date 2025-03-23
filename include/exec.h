/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:44 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/23 15:58:00 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "boolean.h"
# include "get_next_line.h"

typedef struct s_core		t_core;
typedef struct s_commande	t_cmd;

typedef struct s_here_doc
{
	char				*limiter;
	t_boolean			is_pipe;
	int					pipe_here[2];
	struct s_here_doc	*next;
}		t_here_doc;

typedef struct s_exec
{
	int			nb_cmd;
	int			nb_here_doc;
	int			**pipe;
	int			**pipe_here_doc;
	int			fd_infile;
	int			nb_pipe_here_doc;
	int			fd_outfile;
	int			here_doc;
	int			count;
	char		**env_path;
	char		*path;
	char		**env;
	char		**limiter;
	int			**tmp_pipe_here_doc;
	int			*child_pid;
	t_file		*in;
	t_file		*out;
	t_boolean	file_or_not;
	t_boolean	absolute_path;
	t_cmd		*cmd;
	t_here_doc	*here;
	t_here_doc	*here_tmp;
}	t_exec;

//START DE L'EXEC
int			main_exec(t_glb *global, t_core *core);
//FILES
t_boolean	parse_files(t_exec *exec, t_core *core);
int			outfile_manager(t_exec *exec, t_core *core, int fd_in);
int			infile_manager(t_exec *exec, t_core *core);

//HERE_DOC
void		signal_here_doc(void);
void		print_error(void);
void		close_node_pipe(t_here_doc *here);
int			get_here_doc_nb(t_exec *exec);
t_boolean	incr_here_doc(t_cmd *cmd);
t_boolean	here_doc_init(t_exec *exec);
t_boolean	here_doc_manager(t_exec *exec, t_core *core);
t_boolean	ishere_doc(t_exec *exec);
t_here_doc	*new_here_doc(char *file);
void		hereadd_back(t_here_doc **lst, t_here_doc *new);

//BIG EXEC
t_boolean	child_dup(t_exec *exec, int count, t_core *core);
t_boolean	is_builtin(t_cmd *cmd);
int			env_exec(t_exec *exec, t_core *core);
t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count);
void		fd_setup(t_glb *global, int *pipe_fd);
t_boolean	fork_setup(t_exec *exec, t_core *core);
int			fork_previous(t_core *core, t_exec *exec);

//  UTILS EXEC
t_boolean	is_a_directory(char *arg);
void		free_all(t_glb *global);
void		close_pipes(t_exec *exec);

// PIPE
void		free_here_doc(t_exec *exec);
void		close_free_pipes(t_exec *exec);
void		close_pipes_here(t_exec *exec);
void		close_pipes(t_exec *exec);
int			**create_pipe_array(int pipe_nb);
void		free_pipe(int nb_pipe, int **pipe);

void		free_here_doc_node(t_here_doc *here);
t_boolean	env_parse(t_core *core);

#endif
