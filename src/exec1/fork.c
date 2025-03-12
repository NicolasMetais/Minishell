/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:14:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/12 21:23:34 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_boolean	here_doc_or_not(t_exec *exec)
{
	if (pipex->here_doc == true)
		here_doc(pipex);
	else
	{ 
	if (exec->cmd->in_fd[0] == 3)
	{
		if (dup2(exec->cmd->in_fd[0], STDIN_FILENO) == -1)
			return (false);
	}
	close(pipex->input_fd);
	}
	return (true);
} */

void	update_exit_code(t_core *core, pid_t *child_pid)
{
	int		status;
	int		i;
	int		exit_status;
	pid_t	pid;

	i = 0;
	while (child_pid[i] > 0)
	{
		pid = waitpid(child_pid[i], &status, 0);
		if (pid > 0 && WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				core->exit_code = exit_status;
		}
		i++;
	}
}

t_boolean	fork_setup(t_exec *exec, t_core *core)
{
	int		i;
	pid_t	pid;
	pid_t	*child_pid;

	i = 0;
	child_pid = malloc(sizeof(pid_t) * (exec->nb_cmd + 1));
	if (!child_pid)
		return (false);
	while (i < exec->nb_cmd)
	{
		core->exit_code = 0;
		if (pipe(exec->pipe) == -1)
			return (false);
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
	update_exit_code(core, child_pid);
	return (free(child_pid), true);
}
