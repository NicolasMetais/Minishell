/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:27:58 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/14 08:26:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	child_stdin(t_exec *exec)
{
	if (exec->cmd->in)
	{
		while (exec->cmd->in)
		{
			if (!exec->cmd->in->next)
				break ;
				exec->cmd->in = exec->cmd->in->next;
		}
			exec->fd_infile = open(exec->cmd->file, O_RDONLY);
		if (exec->fd_infile < 0)
			return (false);
		if (dup2(exec->fd_infile, STDIN_FILENO) == -1)
			return (false);
	}
	else
	{
		if (dup2(exec->pipe[0], STDIN_FILENO) < 0)
			return (false);
	}
	return (true);
}

t_boolean	child_stdout(t_exec *exec)
{
	if (exec->cmd->out)
	{
		while (exec->cmd->out)
		{
			if (!exec->cmd->out)
				break ;
				exec->cmd->out = exec->cmd->out->next;
		}
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
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (false);
	}
	return (false);
}


t_boolean	child_dup(t_exec *exec, t_cmd *cmd)
{

	child_stdin(exec);
	child_stdout(exec);
	close(exec->fd_outfile);
	close(exec->fd_infile);
	close(exec->pipe[0]);
	close(exec->pipe[1]);
	return (true);
}

t_boolean	parent_process(t_exec *exec)
{
	close(exec->pipe[1]);
	close(exec->pipe[0]);
	return (true);
}

t_boolean	fork_process(t_exec *exec, pid_t pid, t_core *core, int count)
{
	//struct sigaction	sa;

	g_signal = 1;
	if (pid == 0)
	{
		//temporaire c'est normer sans les comms
/* 		if (ft_strcmp(exec->cmd->args[0], "./minishell") == 0)
		{
			sa.sa_handler = SIG_IGN;
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = 0;
			sigaction(SIGINT, &sa, NULL);
		}
		signal_reset(); */
		if (!child_dup(exec, exec->cmd, count))
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
