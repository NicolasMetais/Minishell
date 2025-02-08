/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:53:42 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 20:26:27 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	*new_gc(void *data)
{
	t_gc	*lst;
	int		i;

	i = 0;
	lst = malloc(sizeof(t_gc));
	if (!lst)
		return (NULL);
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void	*gc_malloc(t_gc	**gc, unsigned int size)
{
	void	*data;
	t_gc	*new;

	data = malloc(size);
	if (!data)
		return (NULL);

	new = new_gc(data);
	if (!new)
		return (free(data), NULL);
	if (*gc == NULL)
		*gc = new;
	else
	{
		new->next = *gc;
		*gc = new;
	}
	return (data);
}

void	free_gc(t_gc *gc)
{
	t_gc	*temp;

	while (gc)
	{
		temp = gc;
		gc = gc->next;
		free(temp->data);
		free(temp);
	}
}

void	add_to_gc(t_gc **gc, void *data)
{
	t_gc	*new;

	new = new_gc(data);
	if (!new)
		return (free(data), (void)0);
	if (*gc == NULL)
	{
		*gc = new;
	}
	else
	{
		new->next = *gc;
		*gc = new;
	}
}
