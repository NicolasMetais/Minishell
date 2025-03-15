/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:14:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/15 11:44:06 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_code(t_core *core, pid_t *child_pid)
{
	int		status;
	int		i;
	int		exit_status;
	pid_t	pid;

	i = 0;
	status = 0;
	while (child_pid[i] > 0)
	{
		pid = waitpid(child_pid[i], &status, 0);
		if (pid > 0 && WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				core->exit_code = exit_status;
		}
		if (errno == EINTR)
			continue ;
		i++;
	}
	g_signal = 0;
	wait(NULL);
}

pid_t	*fork_pipe_pid(t_exec *exec)
{
	pid_t	*child_pid;

	child_pid = malloc(sizeof(pid_t) * (exec->nb_cmd + 1));
	if (!child_pid)
		return (NULL);
	exec->pipe = pipe_array(exec);
	if (!exec->pipe)
		return (NULL);
	return (child_pid);
}

t_boolean	fork_setup(t_exec *exec, t_core *core)
{
	int		i;
	pid_t	pid;
	pid_t	*child_pid;

	i = 0;
	child_pid = fork_pipe_pid(exec);
	if (!child_pid)
		return (false);
	while (i < exec->nb_cmd)
	{
		core->exit_code = 0;
		pid = fork();
		if (pid == -1)
			return (false);
		if (pid > 0)
			child_pid[i] = pid;
		if (!fork_process(exec, pid, core, i))
			return (false);
		exec->cmd = exec->cmd->next;
		i++;
	}
	child_pid[i] = 0;
	close_pipes(exec);
	update_exit_code(core, child_pid);
	return (free_pipe(exec), free(child_pid), true);
}
