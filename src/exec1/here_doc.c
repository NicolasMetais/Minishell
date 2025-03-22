/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:46:50 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/23 00:22:41 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	here_doc(t_here_doc *here_doc)
{
	char	*line;
	char	*tmp;
	int		size;

	size = ft_strlen(here_doc->limiter);
	while (1)
	{
		line = readline("here_doc> ");
		if (!line)
		{
			print_error();
			free(line);
			break ;
		}
		if (ft_strncmp(line, here_doc->limiter, size) == 0)
		{
			free(line);
			break ;
		}
		if (here_doc->is_pipe)
		{
			tmp = ft_strjoin(line, "\n");
			if (!tmp)
				return (free(line), false);
			ft_putstr_fd(tmp, here_doc->pipe_here[1]);
			free(tmp);
		}
		free(line);
	}
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
		if (here->is_pipe)
		{
			exec->pipe_here_doc[i] = here->pipe_here;
			close(exec->pipe_here_doc[i][1]);
			i++;
		}
		here = here->next;
	}
	exec->pipe_here_doc[i] = NULL;
	return (true);
}

t_boolean	here_doc_manager(t_exec *exec, t_core *core)
{
	t_here_doc	*here;
	pid_t		pid;

	here = exec->here;
	g_signal = 1;
	pid = fork();
	if (pid == 0)
	{
		signal_here_doc();
		while (here)
		{
			if (!here_doc(here))
				return (false);
			here = here->next;
		}
		here_doc_cleanup(core, exec);
	}
	while (wait(NULL) > 0)
		;
	g_signal = 0;
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
