/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:31:34 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/13 03:38:28 by nmetais          ###   ########.fr       */
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
		{
			exec->here_doc = true;
			in_cpy = in_cpy->next;
			continue ;
		}
		else
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
	t_file	*out_cpy;

	out_cpy = exec->out;
	while (out_cpy)
	{
		if (out_cpy->file == 0)
			exec->fd_outfile = open(out_cpy->file, O_APPEND | O_WRONLY
					| O_TRUNC, 0777);
		else
			exec->fd_outfile = open(out_cpy->file, O_CREAT | O_WRONLY
					| O_TRUNC, 0777);
		if (exec->fd_outfile < 0)
		{
			funct_error("Minishell: ", out_cpy->file, core);
			core->exit_code = errno;
			return (false);
		}
		if (!out_cpy->next)
			break ;
		close(exec->fd_outfile);
		out_cpy = out_cpy->next;
	}
	return (true);
}

void	count_files(t_exec *exec)
{
	t_file	*in;
	t_file	*out;

	in = exec->in;
	out = exec->out;
	while (in)
	{
		exec->nb_files++;
		if (!in->next)
			break ;
		in = in->next;
	}
	while (out)
	{
		exec->nb_files++;
		if (!out->next)
			break ;
		out = out->next;
	}
}

t_boolean	open_files(t_exec *exec, t_core *core)
{
	if (!infile_manager(exec, core))
		return (false);
	if (!outfile_manager(exec, core))
		return (false);
	if (exec->fd_infile)
	{
		if (dup2(exec->fd_infile, STDIN_FILENO) < 0)
			return (false);
		close(exec->fd_infile);
	}
	if (exec->here_doc)
	{
		if (!here_doc_init(exec))
			return (false);
		if (!here_doc_manager(exec))
			return (false);
	}
	count_files(exec);
	return (true);
}
