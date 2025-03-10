/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/10 23:44:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	child_dup(t_exec *exec, int count)
{
	close(exec->pipe[0]);
	if (exec->nb_cmd >= 1 && count == exec->nb_cmd - 1 && exec->fd_outfile)
	{
		if (dup2(exec->fd_outfile, STDOUT_FILENO) == -1)
			return (false);
		close(exec->fd_outfile);
	}
	else if (exec->nb_cmd > 1 && exec->cmd->next)
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (false);
	}
	close(exec->pipe[1]);
	return (true);
}

t_boolean	parent_process(t_exec *exec)
{
	close(exec->pipe[1]);
	if (exec->nb_cmd > 1)
	{
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			return (false);
	}
	close(exec->pipe[0]);
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count)
{
	if (pid == 0)
	{
		signal_reset();
		if (!child_dup(exec, count))
			return (false);
		if (!env_exec(exec, core))
			return (false);
		exit(core->exit_code);
	}
	else
	{
		if (!parent_process(exec))
			return (false);
	}
	return (true);
}
