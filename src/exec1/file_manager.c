/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:31:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/18 01:04:05 by nmetais          ###   ########.fr       */
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

int	infile_manager(t_exec *exec, t_core *core)
{
	t_file	*tmp_file;
	int		fd;

	fd = -2;
	tmp_file = exec->cmd->in;
	while (tmp_file)
	{	
		if (tmp_file->type == 1)
		{
			fd = __open_infile(tmp_file->file, core);
			if (fd == -1)
			{
				open_file_failed(tmp_file->file);
				free_random(exec, core);
				free(exec->pipe_here_doc);
				free_here_doc_node(exec->here_tmp);
				kill_program(core);
				free_global(core->glb);
				exit(1);
			}
		}
		if (!tmp_file->next)
			break ;
		close (fd);
		tmp_file = tmp_file->next;
	}
	return (fd);
}


int	outfile_manager(t_exec *exec, t_core *core)
{
	t_file	*tmp_file;
	int		fd;

	tmp_file = exec->cmd->out;
	fd = -2;
	while (tmp_file)
	{
		fd = __open_outfile(tmp_file);
		if (fd < 0)
		{
			open_file_failed(tmp_file->file);
			free_random(exec, core);
			kill_program(core);
			free_global(core->glb);
			exit(1);
		}
		if (!tmp_file->next)
			break ;
		close(fd);
		tmp_file = tmp_file->next;
	}
	return (fd);
}

t_boolean	parse_files(t_exec *exec, t_core *core)
{
	(void)core;
	if (ishere_doc(exec))
	{
		if (!here_doc_init(exec))
			return (false);
		if (!here_doc_manager(exec))
			return (false);
		core->here = exec->here;
		core->nb_here_doc = exec->nb_here_doc;
		core->nb_pipe_here_doc = exec->nb_pipe_here_doc;
		core->pipe_here_doc = exec->pipe_here_doc;
	}
	return (true);
}
