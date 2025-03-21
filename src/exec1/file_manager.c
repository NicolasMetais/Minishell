/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:31:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 10:31:09 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				kill_open_file_failed(core, exec, tmp_file);
			}
		}
		if (!tmp_file->next)
			break ;
		close (fd);
		tmp_file = tmp_file->next;
	}
	return (fd);
}

int	outfile_manager(t_exec *exec, t_core *core, int fd_in)
{
	t_file	*tmp_file;
	int		fd;

	tmp_file = exec->cmd->out;
	fd = -2;
	while (tmp_file)
	{
		fd = __open_outfile(tmp_file);
		if (fd == -1)
		{
			if (fd_in > 0)
				close(fd_in);
			kill_open_file_failed(core, exec, tmp_file);
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
		if (!here_doc_manager(exec, core))
			return (false);
		core->here = exec->here;
		core->nb_here_doc = exec->nb_here_doc;
		core->nb_pipe_here_doc = exec->nb_pipe_here_doc;
		core->pipe_here_doc = exec->pipe_here_doc;
	}
	return (true);
}
