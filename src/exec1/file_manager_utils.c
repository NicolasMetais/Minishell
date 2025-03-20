/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:52:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/20 19:58:36 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__open_infile(char *file, t_core *core)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		core->exit_code = 1;
		return (-1);
	}
	return (fd);
}

int	__open_outfile(t_file *tmp)
{
	if (tmp->type == 0)
		return (open(tmp->file, O_APPEND | O_WRONLY
				| O_CREAT, 0644));
	else
		return (open(tmp->file, O_CREAT | O_WRONLY
				| O_TRUNC, 0644));
}

void	kill_open_file_failed(t_core *core, t_exec *exec, t_file *tmp_file)
{
	if (is_builtin(exec->cmd) && exec->nb_cmd == 1)
	{	
		if (exec->nb_here_doc > 0)
		{
			close_pipes_here(exec);
			free_here_doc_node(exec->here_tmp);
			free(exec->pipe_here_doc);
		}
		open_file_failed(tmp_file->file);
		return ;
	}
	open_file_failed(tmp_file->file);
	close_pipes_here(exec);
	free_random(exec, core);
	free(exec->pipe_here_doc);
	free_here_doc_node(exec->here_tmp);
	kill_program(core);
	close_pipes(exec);
	free_pipe(exec->nb_cmd - 1, exec->pipe);
	free_global(core->glb, NULL);
	exit(1);
}
