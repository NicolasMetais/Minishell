/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:45:16 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/20 16:38:39 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	child_stdin(t_exec *exec, int count, int fd)
{
	t_file	*in;

	in = exec->cmd->in;
	if (in)
	{
		while (in->next)
			in = in->next;
		if (in->type == 0)
		{
			if (dup2(*exec->tmp_pipe_here_doc[0], STDIN_FILENO) == -1)
				return (false);
		}
		else
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				return (false);
			close(fd);
		}
	}
	else if (count != 0)
	{
		if (dup2(exec->pipe[count - 1][0], STDIN_FILENO) < 0)
			return (false);
	}
	return (true);
}

t_boolean	child_stdout(t_exec *exec, int count, int fd)
{
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (false);
		close(fd);
	}
	else if (exec->nb_cmd > 1 && exec->cmd->next)
	{
		if (dup2(exec->pipe[count][1], STDOUT_FILENO) == -1)
			return (false);
	}
	return (true);
}

void	ft_end_child_dup(t_exec *exec, t_core *core)
{
	if (exec->pipe_here_doc)
		close_pipes_here(exec);
	if (exec->pipe)
		close_pipes(exec);
	if (g_signal == 1)
	{
		close(core->save);
		close(core->save1);
	}
	if (!exec->cmd->args[0])
	{
		free(exec->pipe_here_doc);
		free_here_doc_node(exec->here_tmp);
		free_pipe(exec->nb_cmd - 1, exec->pipe);
		free_random(exec, core);
		kill_program(core);
		free_global(core->glb, NULL);
		exit(1);
	}
	free(exec->pipe_here_doc);
	free_here_doc_node(exec->here_tmp);
}

t_boolean	child_dup(t_exec *exec, int count, t_core *core)
{
	int	fd_out;
	int	fd_in;

	fd_out = outfile_manager(exec, core);
	if (fd_out == -1)
		return (false);
	fd_in = infile_manager(exec, core);
	if (fd_in == -1)
	{
		if (fd_out > 0)
			close(fd_out);
		return (false);
	}
	if (!child_stdin(exec, count, fd_in))
		return (false);
	if (!child_stdout(exec, count, fd_out))
		return (false);
	ft_end_child_dup(exec, core);
	return (true);
}
