/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 18:28:07 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean child_dup(t_exec *exec)
{
	
	/* 	if (i == global->nb_cmd - 1)
		{
			close(global->pipe_fd[0]);
			if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
				return (false);
			close(pipex->outfile_fd);
		}
		else
		{ */
	close(exec->pipe[0]);
	if (exec->nb_cmd > 1 && exec->cmd->next) //GESTION OUTFILE
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (false);

	}
	else if (exec->nb_cmd > 1 && exec->cmd->next)
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (false);
		close(exec->pipe[1]);
	}
	//	close(global->outfile_fd);
	//	}
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core)
{
	if (pid == 0)
	{
		signal_reset();
		if (!child_dup(exec))
			return (false);
		if (!env_exec(exec, core))
			return (false);
		exit(core->exit_code);
	}
	else
	{
		close(exec->pipe[1]);
		if (exec->nb_cmd > 1)
		{
			if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
				return (false);
		}	
		close(exec->pipe[0]);
	}
	return (true);
}
