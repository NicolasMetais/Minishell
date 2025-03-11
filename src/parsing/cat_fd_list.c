/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_fd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-11 12:23:49 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-11 12:23:49 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*cat_fd(t_file *head, t_file *new)
{
	t_file	*tmp;

	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

t_file	*get_all_in(t_cmd *cmd)
{
	t_file	*head;

	head = NULL;
	while (cmd)
	{
		head = cat_fd(head, cmd->in);
		cmd = cmd->next;
	}
	return (head);
}

t_file	*get_all_out(t_cmd *cmd)
{
	t_file	*head;

	head = NULL;
	while (cmd)
	{
		head = cat_fd(head, cmd->out);
		cmd = cmd->next;
	}
	return (head);
}
