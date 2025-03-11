/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:46:50 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/11 05:30:18 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	here_doc_process(t_exec *exec, int i, t_boolean first_input)
{
	char	*line;
	//char	*tmp;
	//int		size;

	line = "\0";
	while (ft_strcmp(line, exec->limiter[i]) != 0)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
		if (!line)
			return (false);
		if (i > 0 && first_input)
		{
			//ICI je doit read sur le PIPE 0 (FAUT REFLECHIR A COMMENT ALLOUER DE LA MEMOIRE DYNAMIQUEMENT)
			//tmp = malloc(sizeof(char) * ft_strlen(line) + ft_strlen())
		}
		close(exec->pipe[0]);
		ft_putstr_fd(line, exec->pipe[1]);
		free(line);
	}
	close(exec->pipe[1]);
	return (true);
}

t_boolean	here_doc(t_exec *exec, int nb_here_doc, t_boolean first_input)
{
	pid_t	pid;

	pipe(exec->pipe);
	pid = fork();
	if (pid == 0)
	{
		if (!here_doc_process(exec, nb_here_doc, first_input))
			return (false);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(exec->pipe[1]);
		if (dup2(exec->pipe[0], STDIN_FILENO))
			return (false);
		close(exec->pipe[0]);
		wait(NULL);
	}
	return (true);
}

t_boolean	here_doc_manager(t_exec *exec)
{
	int	nb_here_doc;

	nb_here_doc = -1;
	while (exec->limiter[++nb_here_doc])
	{
		if (nb_here_doc > 0)
		{
			if (!here_doc(exec, nb_here_doc, true))
				return (false);
		}
		else
		{
			if (!here_doc(exec, nb_here_doc, false))
				return (false);
		}
	}
	return(true);
}

int	get_here_doc_nb(t_file *in_cpy)
{
	int		size;

	size = 0;
	while (in_cpy)
	{
		if (in_cpy->type == 0)
			size++;
		in_cpy = in_cpy->next;
	}
	return (size);
}

t_boolean	here_doc_init(t_exec *exec)
{
	t_file	*in_cpy;
	int		i;

	i = 0;
	in_cpy = exec->in;
	exec->limiter = malloc(sizeof(char *) * (get_here_doc_nb(in_cpy) + 1));
	if (!exec->limiter)
		return (false);
	while (in_cpy)
	{
		if (in_cpy->type == 0)
		{
			exec->limiter[i] = ft_strdup(in_cpy->file);
			if (!exec->limiter[i])
				return (free_tab(exec->limiter), false);
			i++;
		}
		if (!in_cpy->next)
			break ;
		in_cpy = in_cpy->next;
	}
	exec->limiter[i] = NULL;
	return (true);
}
