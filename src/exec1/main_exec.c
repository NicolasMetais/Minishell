/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:26:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/09 02:26:45 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	free_cmd(t_pipex *pipex, int i)
{
	while (i > 0)
	{
		free(pipex->cmd[i]);
		i--;
	}
} */

t_boolean	env_parse(t_exec *exec, t_core *core)
{
	int	i;

	i = 0;
	rotate_env(core, "PATH");
	exec->path = ft_strdup(core->env->var);
	if (!exec->path)
		return (false);
	exec->splitted_path = ft_split(exec->path, ':');
	if (!exec->splitted_path)
		return (false);
	return (true);
}

t_boolean	open_files(t_exec *exec, t_core *core)
{
	int	fd_infile;
	int	fd_outfile;

	while (exec->in)
	{
		printf("infile\n");
		fd_infile = open(exec->in->file, O_RDONLY);
		if (fd_infile < 0)
		{
			funct_error("ts :", NULL, core);
			return (false);
		}
		if (!exec->in->next)
			break ;
		close(fd_infile);
		exec->in = exec->in->next;
	}
	printf("%d\n", fd_infile);
	while (exec->out)
	{
		printf("outfile\n");
		fd_outfile = open(exec->out->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_outfile < 0)
		{
			funct_error("ts :", NULL, core);
			return (false);
		}
		if (exec->out->next)
			break ;
		close(fd_outfile);
		exec->out = exec->out->next;
	}
	return (true);
}

void	exec_init(t_exec *exec, t_glb *global, t_core *core)
{
	exec->file_or_not = false;
	exec->nb_cmd = global->nb_cmd;
	exec->env_path = global->path;
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

	exec_init(&exec, global, core);
	if (!env_parse(&exec, core))
		return (false);
	if (exec.file_or_not)
	{
		if (!open_files(&exec, core))
			return (false);
		//SI UNE SEULE REDIRECTION OU QUE DES REDIRECTIONS, FERMER TOUT LES FD ET NE RIEN FAIRE ICI
	}
	if (!fork_setup(&exec, core))
		return (false);
	return (true);
}
