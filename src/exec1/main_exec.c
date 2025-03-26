/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/26 09:29:48 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	update_splitted_path(t_core *core)
{
	core->splitted_path[0] -= 5;
	free_tab(core->splitted_path);
	if (!env_parse(core))
		return (false);
	core->splitted_path[0] += 5;
	return (true);
}

t_boolean	exec_init(t_exec *exec, t_glb *global, t_core *core)
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
	core->pipe_here_doc = NULL;
	exec->here_tmp = NULL;
	if (!update_splitted_path(core))
		return (false);
	return (true);
}

t_boolean	launch_fork(t_exec *exec, t_core *core)
{
	if (is_builtin(exec->cmd) && exec->nb_cmd == 1)
	{
		if (!child_dup(exec, 0, core))
			return (true);
		if (!builtin(core, exec->cmd, 0))
		{
			free_global(core->glb, NULL);
			free_env(core);
			return (false);
		}
	}
	else
	{
		if (!fork_previous(core, exec))
		{
			close_free_pipes(exec);
			free_here_doc(exec);
			free_env(core);
			core->splitted_path -= 5;
			free(core->splitted_path);
			free_global(core->glb, NULL);
			return (false);
		}
	}
	return (true);
}

int	main_exec(t_glb *global, t_core *core)
{
	t_exec	exec;

	core->save = dup(STDIN_FILENO);
	core->save1 = dup(STDOUT_FILENO);
	if (!exec_init(&exec, global, core))
		return (false);
	if (!parse_files(&exec, core))
		return (false);
	exec.here_tmp = exec.here;
	if (g_signal != 130)
	{
		if (!launch_fork(&exec, core))
			return (false);
	}
	else
		here_doc_cleanup(core, &exec);
	if (!restore_stdio(core))
		return (false);
	return (true);
}
