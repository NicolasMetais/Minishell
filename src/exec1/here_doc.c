/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:46:50 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 00:51:50 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	here_doc(t_exec *exec, int i, int *here_doc_pos, int *j)
{
	char	*line;
	int		size;

	size = ft_strlen(exec->limiter[i]);
	while (1)
	{
		ft_putstr_fd("here_doc> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, exec->limiter[i], size) == 0
			&& line[size] == '\n')
		{
			free(line);
			break ;
		}
		if (here_doc_pos[i] != -1)
			ft_putstr_fd(line, exec->pipe_here_doc[*j][1]);
		free(line);
	}
	if (here_doc_pos[i] != -1)
		close(exec->pipe_here_doc[(*j)++][1]);
	return (true);
}

void	init_here_doc_vars(int *i, int *j, t_cmd **cmd, t_exec *exec)
{
	*i = 0;
	*j = 0;
	*cmd = exec->cmd;
}

int	*find_last_here_doc_cmd(t_exec *exec, int *here_doc_pos)
{
	t_cmd	*cmd;
	t_file	*infile;
	int		i;
	int		j;
	int		save;

	init_here_doc_vars(&i, &j, &cmd, exec);
	while (cmd)
	{
		save = i;
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0)
				i++;
			infile = infile->next;
		}
		if (i > save)
			here_doc_pos[j++] = i;
		else
			here_doc_pos[j++] = -1;
		cmd = cmd->next;
	}
	return (here_doc_pos);
}

t_boolean	process_here_doc(t_exec *exec, int *i, int *j, int *here_doc_pos)
{
	if (!here_doc(exec, *i, here_doc_pos, j))
		return (false);
	(*i)++;
	return (true);
}

t_boolean	here_doc_manager(t_exec *exec, int *i)
{
	int		*here_doc_pos;
	t_cmd	*cmd;
	t_file	*infile;
	int		j;

	j = 0;
	here_doc_pos = malloc(sizeof(int) * (exec->nb_cmd + 1));
	if (!here_doc_pos)
		return (false);
	here_doc_pos = find_last_here_doc_cmd(exec, here_doc_pos);
	cmd = exec->cmd;
	while (cmd)
	{
		infile = cmd->in;
		while (infile)
		{
			if (infile->type == 0
				&& !process_here_doc(exec, i, &j, here_doc_pos))
				return (false);
			infile = infile->next;
		}
		cmd = cmd->next;
	}
	return (true);
}

