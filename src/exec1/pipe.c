/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:56:42 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/23 15:58:19 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_here(t_exec *exec)
{
	int	n;

	n = 0;
	while (n < exec->nb_pipe_here_doc)
	{
		close(exec->pipe_here_doc[n][0]);
		n++;
	}
}

void	close_pipes(t_exec *exec)
{
	int	n;

	n = 0;
	while (n < exec->nb_cmd - 1)
	{
		close(exec->pipe[n][0]);
		close(exec->pipe[n][1]);
		n++;
	}
}

void	free_failed_pipe(int **array, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		if (array[i][0] > 0)
			close(array[i][0]);
		if (array[i][1] > 0)
			close(array[i][1]);
		free(array[i]);
		i++;
	}
	free(array);
}

int	**create_pipe_array(int pipe_nb)
{
	int	**array;
	int	i;

	array = malloc(sizeof(int *) * (pipe_nb));
	if (!array)
		return (0);
	i = 0;
	while (i < pipe_nb)
	{
		array[i] = malloc(sizeof(int) * 3);
		if (!array[i])
			return (free_failed_pipe(array, i), NULL);
		array[i][2] = 0;
		if (pipe(array[i]) == -1)
		{
			array[i][0] = -1;
			array[i][1] = -1;
			return (free_failed_pipe(array, i), NULL);
		}
		i++;
	}
	return (array);
}

void	free_pipe(int nb_pipe, int **pipe)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		free(pipe[i]);
		i++;
	}
	free(pipe);
}
