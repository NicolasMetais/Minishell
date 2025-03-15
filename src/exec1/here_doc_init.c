/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:59:20 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 00:51:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_here_doc_nb(t_exec *exec)
{
	t_cmd	*cmd;
	t_file	*infile;
	int		size;

	cmd = exec->cmd;
	size = 0;
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
				size++;
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	return (size);
}

t_boolean	ishere_doc(t_exec *exec)
{
	t_cmd	*cmd;
	t_file	*infile;

	cmd = exec->cmd;
	infile = exec->cmd->in;
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
				return (true);
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	return (false);
}

t_boolean	here_doc_pipe(t_exec *exec)
{
	t_cmd	*cmd;
	t_file	*infile;
	int		size;

	cmd = exec->cmd;
	size = 0;
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
			{
				size++;
				break ;
			}
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	exec->pipe_here_doc = create_pipe_array(size);
	if (!exec->pipe_here_doc)
		return (false);
	return (true);
}

t_boolean	here_doc_limiter(t_exec *exec, int *i)
{
	t_cmd	*cmd;
	t_file	*infile;

	cmd = exec->cmd;
	exec->limiter = malloc(sizeof(char *) * (exec->nb_here_doc + 1));
	if (!exec->limiter)
		return (false);
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
			{
				exec->limiter[*i] = ft_strdup(infile->file);
				if (!exec->limiter[*i])
					return (free_tab(exec->limiter), false);
				(*i)++;
			}
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	exec->limiter[*i] = NULL;
	return (true);
}

t_boolean	here_doc_init(t_exec *exec)
{
	int	i;

	i = 0;
	exec->nb_here_doc = get_here_doc_nb(exec);
	if (!here_doc_pipe(exec))
		return (false);
	if (!here_doc_limiter(exec, &i))
		return (false);
	return (true);
}
