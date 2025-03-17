/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:59:20 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 14:31:09 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_boolean	here_doc_pipe(t_exec *exec)
{
	t_cmd		*cmd;
	t_file		*infile;
	t_here_doc	*here;

	here = exec->here;
	cmd = exec->cmd;
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
			{
				if (infile->next == NULL)
					pipe(here->pipe_here);
				else
					here->pipe_here = NULL;
				here = here->next;
			}
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	return (true);
}

t_boolean	create_here(t_exec *exec, t_file *infile)
{
	char		*file;
	t_exec		*here;

	here = exec;
	file = ft_strdup(infile->file);
	if (!file)
		return (free_here_doc(here), false);
	if (!exec->here)
		exec->here = new_here_doc(file);
	else
		hereadd_back(&exec->here, new_here_doc(file));
	if (!exec->here)
		return (free_here_doc(here), false);
	return (true);
}

t_boolean	here_doc_limiter(t_exec *exec)
{
	t_cmd		*cmd;
	t_file		*infile;

	cmd = exec->cmd;
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
			{
				if (!create_here(exec, infile))
					return (false);
			}
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	return (true);
}

t_boolean	here_doc_init(t_exec *exec)
{
	exec->nb_here_doc = get_here_doc_nb(exec);
	if (!here_doc_limiter(exec))
		return (false);
	if (!here_doc_pipe(exec))
		return (false);
	return (true);
}
