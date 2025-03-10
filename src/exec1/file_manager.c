/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:31:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/09 22:33:44 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	infile_manager(t_exec *exec, t_core *core)
{
	t_file	*in_cpy;

	in_cpy = exec->in;
	while (in_cpy)
	{
		if (in_cpy->type == 0)
			in_cpy = in_cpy->next;
		exec->fd_infile = open(in_cpy->file, O_RDONLY);
		if (exec->fd_infile < 0)
		{
			funct_error("Minishell: ", in_cpy->file, core);
			core->exit_code = errno;
			return (false);
		}
		if (!in_cpy->next)
			break ;
		close(exec->fd_infile);
		in_cpy = in_cpy->next;
	}
	return (true);
}

t_boolean	outfile_manager(t_exec *exec, t_core *core)
{
	while (exec->out)
	{
		fprintf(stderr, "ICI\n");
		if (exec->out->file == 0)
		{
			exec->fd_outfile = open(exec->out->file, O_APPEND | O_WRONLY
					| O_TRUNC, 0777);
		}
		else
		{
			fprintf(stderr, ":LA\n");
			exec->fd_outfile = open(exec->out->file, O_CREAT | O_WRONLY
					| O_TRUNC, 0777);
		}
		if (exec->fd_outfile < 0)
		{
			funct_error("Minishell: ", exec->out->file, core);
			core->exit_code = errno;
			return (false);
		}
		if (!exec->out->next)
			break ;
		close(exec->fd_outfile);
		exec->out = exec->out->next;
	}
	return (true);
}

t_boolean	open_files(t_exec *exec, t_core *core)
{
	if (!infile_manager(exec, core))
		return (false);
	if (!outfile_manager(exec, core))
		return (false);
	return (true);
}