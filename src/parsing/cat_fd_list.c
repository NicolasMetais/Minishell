/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_fd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:23:49 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 17:21:49 by nmetais          ###   ########.fr       */
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

void	the_arno(t_glb *glb)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = glb->cmd;
	while (tmp)
	{
		if ((tmp->out || tmp->in) && (tmp->args[0]
				&& ft_strncmp(tmp->args[0], "./"
					, 2) == 0))
		{
			if (tmp->out)
			{
				free_list_fd(tmp->out);
				tmp->out = NULL;
			}
			if (tmp->in)
			{
				free_list_fd(tmp->in);
				tmp->in = NULL;
			}
		}
		tmp = tmp->next;
	}
}
