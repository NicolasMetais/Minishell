/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/10 01:56:10 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	child_dup(t_exec *exec, int count)
{
	close(exec->pipe[0]);
	(void)count;
	if (exec->nb_cmd > 1 && count == exec->nb_cmd - 1 && exec->fd_outfile)
	{
//		printf("OUTFILE\n");
		if (dup2(exec->fd_outfile, STDOUT_FILENO) == -1)
			return (false);
		close(exec->fd_outfile);
	}
	else if (exec->nb_cmd > 1 && exec->cmd->next)
	{
//		fprintf(stderr, "STDOUT - REGULAR\n");
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (false);
	}
	close(exec->pipe[1]);
	close(exec->fd_infile);
	return (true);
}

t_boolean	parent_process(t_exec *exec, int count)
{
	(void)count;
	close(exec->pipe[1]);
	if (exec->nb_cmd > 1 && count == 0 && exec->fd_infile)
	{
//		printf("STDIN - INFILE\n");
		if (dup2(exec->fd_infile, STDIN_FILENO) < 0)
			return (false);
	}
	else if (exec->nb_cmd > 1)
	{
//		printf("STDIN - REGULAR\n");
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			return (false);
	}
	close(exec->fd_infile);
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
		if (!parent_process(exec, count))
			return (false);
	}
	return (true);
}
