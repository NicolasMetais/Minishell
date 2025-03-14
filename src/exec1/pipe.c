/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-14 21:56:42 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-14 21:56:42 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (i < n)
	{
		close(array[i][0]);
		close(array[i][1]);
		free(array[i]);
	}
	free(array);
}

int	**pipe_array(t_exec *exec)
{
	int	**array;
	int	i;

	array = malloc(sizeof(int *) * (exec->nb_cmd - 1));
	if (!array)
		return (0);
	i = 0;
	while (i < exec->nb_cmd - 1) 
	{
		array[i] = malloc(sizeof(int) * 3);
		if (!array[i])
			return (free_failed_pipe(array, i), NULL);
		array[i][2] = 0;
		if (pipe(array[i]) == -1)
		 	return (free_failed_pipe(array, i), NULL);
		i++;
	}
	fprintf (stderr, "nb_pipe : %d\n", i);
	return (array);
}

void	free_pipe(t_exec *exec)
{
	int	i;

    i = 0;
	while (i < exec->nb_cmd - 1)
	{
		free(exec->pipe[i]);
		i++;
	}
	free(exec->pipe);
}
