/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:46:50 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 18:26:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	here_doc(t_here_doc *here_doc)
{
	char	*line;
	int		size;

	size = ft_strlen(here_doc->limiter);
	while (1)
	{
		ft_putstr_fd("here_doc> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, here_doc->limiter, size) == 0
			&& line[size] == '\n')
		{
			free(line);
			break ;
		}
		if (here_doc->pipe_here)
			ft_putstr_fd(line, here_doc->pipe_here[1]);
		free(line);
	}
	if (here_doc->pipe_here)
		close(here_doc->pipe_here[1]);
	return (true);
}

t_boolean	here_doc_array(t_exec *exec)
{
	int			i;
	t_here_doc	*here;

	i = 0;
	here = exec->here;
	exec->pipe_here_doc = malloc(sizeof(int *) * (exec->nb_pipe_here_doc + 1));
	if (!exec->pipe_here_doc)
		return (false);
	while (here)
	{
		if (here->pipe_here)
			exec->pipe_here_doc[i++] = here->pipe_here;
		here = here->next;
	}
	exec->pipe_here_doc[i] = NULL;
	return (true);
}

t_boolean	here_doc_manager(t_exec *exec)
{
	t_here_doc	*here;

	here = exec->here;
	while (here)
	{
		if (!here_doc(here))
			return (false);
		if (here->pipe_here)
			exec->nb_pipe_here_doc++;
		here = here->next;
	}
	if (!here_doc_array(exec))
		return (false);
	exec->tmp_pipe_here_doc = exec->pipe_here_doc;
	return (true);
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
