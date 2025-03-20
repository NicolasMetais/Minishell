/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/20 00:14:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_exec *exec, t_glb *global, t_core *core)
{
	exec->file_or_not = false;
	exec->limiter = NULL;
	exec->here_doc = false;
	exec->fd_infile = 0;
	exec->fd_outfile = 0;
	exec->here_doc = 0;
	exec->nb_cmd = global->nb_cmd;
	exec->absolute_path = false;
	exec->cmd = global->cmd;
	exec->env = core->env_dup;
	exec->in = global->cmd->in;
	exec->count = 0;
	exec->out = global->cmd->out;
	exec->here = NULL;
	exec->nb_pipe_here_doc = 0;
	exec->nb_here_doc = 0;
	exec->pipe_here_doc = NULL;
	exec->pipe = NULL;
	exec->child_pid = NULL;
	core->splitted_path[0] -= 5;
	free_tab(core->splitted_path);
	env_parse(core);
	core->splitted_path[0] += 5;
	core->pipe_here_doc = NULL;
	exec->here_tmp = NULL;
}

t_boolean	launch_fork(t_exec *exec, t_core *core)
{
	if (is_builtin(exec->cmd) && exec->nb_cmd == 1)
	{
		child_dup(exec, 0, core);
		if (!builtin(core, exec->cmd, 0))
			return (false);
	}
	else
	{
		if (!fork_setup(exec, core))
			return (false);
	}
	return (true);
}

int	main_exec(t_glb *global, t_core *core)
{
	t_exec	exec;

	exec_init(&exec, global, core);
	if (!parse_files(&exec, core))
		return (false);
	exec.here_tmp = exec.here;
	if (!launch_fork(&exec, core))
		return (false);
	if (!restore_stdio(core))
		return (false);
	return (true);
}
