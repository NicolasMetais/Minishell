/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:32:18 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/26 12:16:57 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_here_doc(t_exec *exec)
{
	t_here_doc	*tmp_here;

	free_pipe(exec->nb_pipe_here_doc, exec->pipe_here_doc);
	while (exec->here)
	{
		tmp_here = exec->here->next;
		free(exec->here->limiter);
		free(exec->here);
		exec->here = tmp_here;
	}
}

void	close_free_pipes(t_exec *exec)
{
	if (exec && exec->nb_pipe_here_doc > 0)
	{
		close_pipes_here(exec);
		free(exec->pipe_here_doc);
	}
	if (exec && exec->nb_cmd > 1)
	{
		close_pipes(exec);
		free_pipe(exec->nb_cmd - 1, exec->pipe);
	}
}
