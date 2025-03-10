/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-08 12:28:20 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-08 12:28:20 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*add_to_file_list(t_file *lst, t_file *new)
{
	t_file	*tmp;

	if (!lst)
	{
		tmp = NULL;
		return (new);
	}
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

t_file	*init_list(char *file, t_file *list, t_type_red type, int complete)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (free_list_fd(list), NULL);
	new->type = type;
	if (complete == 1)
		new->complete = true;
	else
		new->complete = false;
	new->file = file;
	new->next = NULL;
	list = add_to_file_list(list, new);
	return (list);
}

t_file	*list_complete(char *file, t_file *list, t_type_red type, int comp)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (free_list_fd(list), NULL);
	new->type = type;
	if (comp == 1)
		new->complete = true;
	else
		new->complete = false;
	new->file = file;
	new->next = NULL;
	list = add_to_file_list(list, new);
	return (list);
}

t_file	*create_file(char *file, t_file *list, t_type_red type, int complete)
{
	t_file	*tmp;

	if (!list)
	{	
		list = init_list(file, list, type, complete);
		if (!list)
			return (NULL);
	}
	else if (list->complete == true)
	{
		list = list_complete(file, list, type, complete);
		if (!list)
			return (NULL);
	}
	else if (list->complete == false)
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		list->file = file;
		list->complete = true;
		return (list);
	}
	return (list);
}

void	add_file_to_cmd(char *file, char c, t_cmd *cmd, t_red *tab_red)
{
	cmd->error = 0;
	if (c == '<')
	{	
		cmd->in = create_file(file, cmd->in, tab_red->type, 1);
		if (!cmd->in)
		{
			cmd->error = 1;
			free_list_fd(cmd->out);
		}	
	}
	else
	{
		cmd->out = create_file(file, cmd->out, tab_red->type, 1);
		if (!cmd->out)
		{	
			cmd->error = 1;
			free_list_fd(cmd->in);
		}
	}
}
