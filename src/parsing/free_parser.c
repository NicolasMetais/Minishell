/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:45:54 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/03 22:48:52 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

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
	int	n;

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
	if (cmd->args)
		free_split(cmd->args);
	if (cmd->here_doc)
		free_split(cmd->here_doc);
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
	if (glb)
	{
		if (glb->cmd)
			freelist(glb->cmd);
		if (glb->path)
			free_split(glb->path);
		free(glb);
	}
}
