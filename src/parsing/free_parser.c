/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 12:45:54 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-07 12:45:54 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_split_init(char **split, int i)
{
	int n;

	n = 0;
	while (n < i)
	{
		free(split[n]);
		n++;
	}
	free(split);
}

void	free_node(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	if (cmd->cmd)
		free_split(cmd->cmd);
	if (cmd->here_doc)
		free(cmd->here_doc);
	free(cmd);
}

void	freelist(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free_node(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}

void	free_global(t_glb *glb)
{
	if (glb->cmd)
		free_list(glb->cmd);
	if (glb->path)
		free_split(glb->path);
	free(glb);
}