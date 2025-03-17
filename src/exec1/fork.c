/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 02:14:47 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 16:20:08 by nmetais          ###   ########.fr       */
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
}

void	fork_pipe_pid(t_exec *exec)
{
	exec->child_pid = malloc(sizeof(pid_t) * (exec->nb_cmd + 1));
	if (!exec->child_pid)
		return ;
	if (exec->nb_cmd > 1)
	{
		exec->pipe = create_pipe_array(exec->nb_cmd - 1);
		if (!exec->pipe)
			free(exec->child_pid);
	}
}

t_boolean	incr_here_doc(t_cmd *cmd)
{
	t_file	*infile;

	infile = cmd->in;
	while (infile && infile->next)
		infile = infile->next;
	if (infile && infile->type == 0)
		return (true);
	return (false);
}

t_boolean	fork_setup(t_exec *exec, t_core *core)
{
	pid_t	pid;

	fork_pipe_pid(exec);
	if (!exec->child_pid)
		return (false);
	g_signal = 1;
	while (exec->count < exec->nb_cmd)
	{
		core->exit_code = 0;
		pid = fork();
		if (pid == -1)
			return (false);
		if (pid > 0)
			exec->child_pid[exec->count] = pid;
		if (!fork_process(exec, pid, core, exec->count))
			return (false);
		exec->cmd = exec->cmd->next;
		exec->count++;
	}
	exec->child_pid[exec->count] = 0;
	close_free_pipes(exec);
	update_exit_code(core, exec->child_pid);
	if (exec->nb_pipe_here_doc > 0)
		free_here_doc_node(exec->here_tmp);
	return (free(exec->child_pid), true);
}
