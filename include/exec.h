/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:44 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/10 23:23:46 by nmetais          ###   ########.fr       */
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
	char		**env_path;
	int			pipe[2];
	char		*path;
	char		**splitted_path;
	char		**env;
	t_file		*in;
	t_file		*out;
	int			fd_infile;
	int			fd_outfile;
	t_boolean	file_or_not;
	t_boolean	absolute_path;
	t_cmd		*cmd;
}	t_exec;

int			main_exec(t_glb *global, t_core *core);

void		free_all(t_glb *global);

t_boolean	env_parse(t_core *core);
t_boolean	args_parse(t_glb *global);

int			env_exec(t_exec *exec, t_core *core);
t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count);
void		fd_setup(t_glb *global, int *pipe_fd);

void		here_doc(t_glb *global);

t_boolean	open_files(t_exec *exec, t_core *core);

t_boolean	fork_setup(t_exec *exec, t_core *core);

#endif
