/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 23:32:26 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	child_stdin(t_exec *exec, int count, int fd)
{
	if (exec->cmd->in)
	{
		while (exec->cmd->in->next)
			exec->cmd->in = exec->cmd->in->next;
		if (exec->cmd->in->type == 0)
		{
			if (dup2(*exec->tmp_pipe_here_doc[0],
					STDIN_FILENO) == -1)
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
	if (exec->pipe_here_doc)
		close_pipes_here(exec);
	if (exec->pipe)
		close_pipes(exec);
	return (true);
}

t_boolean	parent_process(t_exec *exec)
{
	if (ft_strncmp(exec->cmd->args[0], "./", 2) == 0)
	{
		g_signal = 1;
		signal_update();
	}
	if (incr_here_doc(exec->cmd))
		exec->tmp_pipe_here_doc++;
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count)
{
	if (pid == 0)
	{
		if (!child_dup(exec, count, core))
			execve_error(core, exec, exec->cmd->args[0]);
		if (is_builtin(exec->cmd))
		{
			if (!(builtin(core, exec->cmd)))
				return (false);
		}
		else
		{
			if (!env_exec(exec, core))
				return (false);
		}
		exit(core->exit_code);
	}
	else
	{
		if (!parent_process(exec))
			return (false);
	}
	return (true);
}
