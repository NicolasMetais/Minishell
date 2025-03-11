/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/12 00:15:53 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_builtin(t_cmd *cmd)
{
	if ((ft_strcmp(cmd->args[0], "cd") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "echo") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "pwd") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "exit") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "env") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "export") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "unset") == 0))
		return (true);
	return (false);
}

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
	close(exec->fd_intfile);
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count)
{
	if (pid == 0)
	{
		signal_reset();
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
