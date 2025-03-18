/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:04:59 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/18 15:47:50 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_node_pipe(t_here_doc *here)
{
	t_here_doc	*tmp;

	tmp = here;
	while (tmp)
	{
		if (tmp->is_pipe)
		{
			close(tmp->pipe_here[0]);
			close(tmp->pipe_here[1]);
		}
		tmp = tmp->next;
	}
}

void	free_here_doc_node(t_here_doc *here)
{
	t_here_doc	*tmp;

	while (here)
	{
		tmp = here->next;
		free(here->limiter);
		here->limiter = NULL;
		free(here);
		here = tmp;
	}
}

t_here_doc	*new_here_doc(char *file)
{
	t_here_doc	*new;

	new = malloc(sizeof(t_here_doc));
	if (!new)
		return (NULL);
	(*new).next = NULL;
	new->limiter = file;
	new->is_pipe = false;
	return (new);
}

void	hereadd_back(t_here_doc **lst, t_here_doc *new)
{
	t_here_doc	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}
