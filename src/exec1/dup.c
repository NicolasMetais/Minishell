/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/19 05:26:39 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	parent_process(t_exec *exec)
{	
	if (exec->cmd->args[0] && ft_strncmp(exec->cmd->args[0], "./", 2) == 0)
	{
		g_signal = 1;
		signal_mute();
	}
	if (incr_here_doc(exec->cmd))
		exec->tmp_pipe_here_doc++;
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count)
{
	if (pid == 0)
	{
		signal_fork();
		if (!child_dup(exec, count, core))
			execve_error(core, exec, exec->cmd->args[0]);
		if (is_builtin(exec->cmd))
		{
			if (!(builtin(core, exec->cmd, 1)))
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
