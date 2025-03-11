/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/12 00:15:01 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_boolean	env_parse(t_core *core)
{
	int	i;

	i = 0;
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
	exec->fd_infile = 0;
	exec->fd_outfile = 0;
	exec->nb_cmd = global->nb_cmd;
	exec->env_path = core->splitted_path;
	exec->absolute_path = false;
	exec->cmd = global->cmd;
	exec->env = core->env_dup;
	exec->in = global->cmd->in;
	exec->out = global->cmd->out;
	if (exec->in || exec->out)
		exec->file_or_not = true;
}

int	main_exec(t_glb *global, t_core *core)
{
	t_exec	exec;

	if (!env_parse(core))
		return (false);
	exec_init(&exec, global, core);
	if (exec.file_or_not)
	{
		if (!open_files(&exec, core))
			return (false);
		if (!here_doc_init(&exec))
			return (false);
		if (!here_doc_manager(&exec))
			return (false);
	}
	if (!fork_setup(&exec, core))
		return (false);
	return (free(core->path), free_split(core->splitted_path), true);
}
