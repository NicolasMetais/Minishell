/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:04:59 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/16 18:05:33 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_here_doc	*new_here_doc(char *file)
{
	t_here_doc	*new;

	new = malloc(sizeof(t_here_doc));
	if (!new)
		return (NULL);
	(*new).next = NULL;
	new->limiter = file;
	new->pipe_here = malloc(sizeof(int) * 2);
	if (!new->pipe_here)
		return (NULL);
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
