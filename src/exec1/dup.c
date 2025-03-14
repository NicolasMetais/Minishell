/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/14 19:06:26 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	child_stdin(t_exec *exec, int count)
{
	if (exec->cmd->in)
	{
		while (exec->cmd->in->next)
			exec->cmd->in = exec->cmd->in->next;
		exec->fd_infile = open(exec->cmd->in->file, O_RDONLY);
		if (exec->fd_infile < 0)
			return (false);
		if (dup2(exec->fd_infile, STDIN_FILENO) == -1)
			return (false);
	}
	else if (count != 0)
	{
		if (dup2(exec->pipe[count - 1][0], STDIN_FILENO) < 0)
			return (false);
	}
	return (true);
}

t_boolean	child_stdout(t_exec *exec, int count)
{

	if (exec->cmd->out)
	{
		while (exec->cmd->out->next)
			exec->cmd->out = exec->cmd->out->next;
		if (exec->cmd->out->type == 0)
			exec->fd_outfile = open(exec->cmd->out->file, O_APPEND | O_WRONLY
					| O_APPEND, 0644);
		else
			exec->fd_outfile = open(exec->cmd->out->file, O_CREAT | O_WRONLY
					| O_TRUNC, 0644);
		if (exec->fd_outfile < 0)
			return (false);
		if (dup2(exec->fd_outfile, STDOUT_FILENO) == -1)
			return (false);
	}
	else if (exec->nb_cmd > 1 && exec->cmd->next)
	{

		if (dup2(exec->pipe[count][1], STDOUT_FILENO) == -1)
			return (false);
	}
	return (true);
}

t_boolean	child_dup(t_exec *exec, int count)
{

	if (!child_stdin(exec, count))
		return (false);
	if (!child_stdout(exec, count))
		return (false);
	if (exec->pipe)
		close_pipes(exec);
	if (exec->fd_infile > 0)
		close(exec->fd_infile);
	if (exec->fd_outfile > 0)
		close(exec->fd_outfile);
	return (true);
}

t_boolean	parent_process(t_exec *exec)
{
	if (ft_strcmp(exec->cmd->args[0], "./minishell") == 0)
	{
		g_signal = 1;
		signal_update();
	}
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count)
{
	if (pid == 0)
	{
		if (!child_dup(exec, count))
			return (false);
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
