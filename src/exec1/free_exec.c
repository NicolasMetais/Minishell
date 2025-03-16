/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:32:18 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 19:26:29 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_here_doc(t_here_doc *here)
{
	t_here_doc	*tmp_here;

	while (here)
	{
		tmp_here = here->next;
		free(here->limiter);
		free(here->pipe_here);
		free(here);
		here = tmp_here;
	}
}

void	close_free_pipes(t_exec *exec)
{
	close_pipes(exec);
	if (exec->nb_here_doc > 0)
		close_pipes_here(exec);
	free_here_doc(exec->here);
	if (exec->nb_cmd > 1)
		free_pipe(exec->nb_cmd - 1, exec->pipe);
}
