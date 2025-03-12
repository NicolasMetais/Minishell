/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:46:50 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/12 15:32:17 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	here_doc_process(t_exec *exec, int i)
{
	char	*line;
	int		size;

	close(exec->pipe[0]);
	size = ft_strlen(exec->limiter[i]);
	while (1)
	{
		ft_putstr_fd("here_doc> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, exec->limiter[i], size) == 0 && line[size] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, exec->pipe[1]);
		free(line);
	}
	close(exec->pipe[1]);
	return (true);
}

t_boolean	here_doc(t_exec *exec, int nb_here_doc)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!here_doc_process(exec, nb_here_doc))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
	}
	return (true);
}

t_boolean	here_doc_manager(t_exec *exec)
{
	int	nb_here_doc;

	nb_here_doc = -1;
	pipe(exec->pipe);
	while (exec->limiter[++nb_here_doc])
	{
		if (!here_doc(exec, nb_here_doc))
			return (false);
	}
	if (dup2(exec->pipe[0], STDIN_FILENO))
		return (false);
	close(exec->pipe[0]);
	close(exec->pipe[1]);
	return (true);
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
