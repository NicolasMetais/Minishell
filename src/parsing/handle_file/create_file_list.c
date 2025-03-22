/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:28:20 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/19 21:38:10 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*add_to_file_list(t_file **lst, t_file *new)
{
	t_file	*tmp;

	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*lst);
}

t_file	*init_list(char *file, t_file *list, t_type_red type)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (free_list_fd(list), NULL);
	new->type = type;
	if (ft_strlen(file) == 0)
		new->file = ft_strdup("");
	else
		new->file = ft_strdup(file);
	if (!new->file)
		return (NULL);
	new->next = NULL;
	list = new;
	return (list);
}

t_file	*create_file(char *file, t_file *list, t_type_red type)
{
	t_file	*new;

	if (!list)
	{	
		list = init_list(file, list, type);
		if (!list)
			return (NULL);
	}
	else
	{
		new = malloc(sizeof(t_file));
		if (!new)
			return (free_list_fd(list), NULL);
		new->type = type;
		if (ft_strlen(file) == 0)
			new->file = ft_strdup("");
		else
			new->file = ft_strdup(file);
		new->next = NULL;
		if (!new->file)
			return (NULL);
		list = add_to_file_list(&list, new);
	}
	return (list);
}

void	add_file_to_cmd(char *file, char c, t_cmd *cmd, t_red *tab_red)
{
	cmd->error = 0;
	if (c == '<')
	{	
		cmd->in = create_file(file, cmd->in, tab_red->type);
		if (!cmd->in)
		{
			cmd->error = 1;
			free_list_fd(cmd->out);
		}	
	}
	else
	{
		cmd->out = create_file(file, cmd->out, tab_red->type);
		if (!cmd->out)
		{	
			cmd->error = 1;
			free_list_fd(cmd->in);
		}
	}
}
