/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/14 15:23:57 by nmetais          ###   ########.fr       */
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
	exec->here_doc = false;
	exec->fd_infile = 0;
	exec->fd_outfile = 0;
	exec->nb_cmd = global->nb_cmd;
	exec->env_path = core->splitted_path;
	exec->absolute_path = false;
	exec->cmd = global->cmd;
	exec->env = core->env_dup;
	exec->in = global->cmd->in;
	exec->out = global->cmd->out;
	exec->trigger = false;
	if (exec->in || exec->out)
		exec->file_or_not = true;
}

t_boolean	launch_fork(t_exec *exec, t_core *core)
{
	if (exec->nb_cmd > 1 && (ft_strcmp(exec->cmd->args[0], "export") == 0
			|| ft_strcmp(exec->cmd->args[0], "unset") == 0))
	{
		if (!builtin(core, exec->cmd))
			return (false);
		exec->env = core->env_dup;
		exec->cmd = exec->cmd->next;
		exec->nb_cmd = exec->nb_cmd - 1;
		if (!fork_setup(exec, core))
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
