/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:44 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 00:52:59 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "boolean.h"
# include "get_next_line.h"

typedef struct s_core		t_core;
typedef struct s_commande	t_cmd;


typedef struct s_exec
{
	int			nb_cmd;
	int			nb_here_doc;
	int			**pipe;
	int			**pipe_here_doc;
	int			fd_infile;
	int			fd_outfile;
	int			here_doc;
	int			count;
	char		**env_path;
	char		*path;
	char		**splitted_path;
	char		**env;
	char		**limiter;
	t_file		*in;
	t_file		*out;
	t_boolean	file_or_not;
	t_boolean	absolute_path;
	t_cmd		*cmd;
}	t_exec;

//START DE L'EXEC
int			main_exec(t_glb *global, t_core *core);
//PARSING
t_boolean	env_parse(t_core *core);
//FILES
t_boolean	parse_files(t_exec *exec, t_core *core);
//HERE_DOC
t_boolean	incr_here_doc(t_cmd *cmd);
t_boolean	ishere_doc(t_exec *exec);
t_boolean	here_doc_init(t_exec *exec);
t_boolean	here_doc_manager(t_exec *exec, int *i);
t_boolean	multiple_here_doc(t_exec *exec);
//BIG EXEC
t_boolean	is_builtin(t_cmd *cmd);
int			env_exec(t_exec *exec, t_core *core);
t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count);
void		fd_setup(t_glb *global, int *pipe_fd);
t_boolean	fork_setup(t_exec *exec, t_core *core);
//  UTILS EXEC
t_boolean	is_a_directory(char *arg);
void		free_all(t_glb *global);
void		close_pipes(t_exec *exec);

// PIPE
void	close_pipes(t_exec *exec);
int		**create_pipe_array(int pipe_nb);
void	free_pipe(t_exec *exec);

#endif
