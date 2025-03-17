/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:32 by nmetais           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/17 03:43:09 by nmetais          ###   ########.fr       */
=======
/*   Updated: 2025/03/17 14:51:39 by nmetais          ###   ########.fr       */
>>>>>>> debug
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	env_parse(t_core *core)
{
	rotate_env(core, "PATH");
	core->path = ft_strdup(core->env->var);
	if (!core->path)
		return (false);
	core->splitted_path = ft_split(core->path, ':');
	if (!core->splitted_path)
		return (false);
	return (true);
}

void	exec_init(t_exec *exec, t_glb *global, t_core *core)
{
	exec->file_or_not = false;
	exec->limiter = NULL;
	exec->here_doc = false;
	exec->fd_infile = 0;
	exec->fd_outfile = 0;
	exec->here_doc = 0;
	exec->nb_cmd = global->nb_cmd;
	exec->env_path = core->splitted_path;
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
	if (exec->in || exec->out)
		exec->file_or_not = true;
}

t_boolean	launch_fork(t_exec *exec, t_core *core)
{
	if (is_builtin(exec->cmd) && exec->nb_cmd == 1)
	{
		child_dup(exec, 0, core);
		if (!builtin(core, exec->cmd, 0))
			return (false);
	}
	else if (is_builtin(exec->cmd) && exec->nb_cmd == 1)
	{
		child_dup(exec, 0, core);
		if (!builtin(core, exec->cmd))
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

	if (!env_parse(core))
		return (false);
	exec_init(&exec, global, core);
	if (exec.file_or_not)
	{
		if (!parse_files(&exec, core))
			return (false);
	}
	if (!launch_fork(&exec, core))
		return (false);
	return (free(core->path), free_split(core->splitted_path), true);
}
