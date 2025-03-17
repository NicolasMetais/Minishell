/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:32:18 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 03:41:01 by nmetais          ###   ########.fr       */
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
	close_pipes(exec);
	if (exec->nb_here_doc > 0)
	{
		close_pipes_here(exec);
		free_here_doc(exec);
	}
	if (exec->nb_cmd > 1)
		free_pipe(exec->nb_cmd - 1, exec->pipe);
}
