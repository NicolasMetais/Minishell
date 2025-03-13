/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:14:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/13 16:24:27 by nmetais          ###   ########.fr       */
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
	printf("NB CMD %d\n", exec->nb_cmd);
	while (i < exec->nb_cmd)
	{
		fprintf(stderr, "I : %d\n", i);
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
