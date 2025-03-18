/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:45:54 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 00:45:24 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FREE DOUBLE TABLEAU
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

// FREE DOUBLE TABLEAU SI MALLOC FAIL
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

// FREE NODE CMD
void	free_node(t_cmd *cmd)
{
	if (cmd->in)
	{
		fprintf(stderr, "free in : %s\n", cmd->args[0]);
		free_list_fd(cmd->in);
	}
	if (cmd->out)
	{
		fprintf(stderr, "free out : %s\n", cmd->args[0]);
		free_list_fd(cmd->out);
	}
	if (cmd->args)
		free_split(cmd->args);
	free(cmd);
}

// FREE LA LISTE DE COMMANDE
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

//FREE LE GLOBAL
void	free_global(t_glb *glb)
{
	if (glb)
	{
		if (glb->cmd)
			freelist(glb->cmd);
		free(glb);
		glb = NULL;
	}
}
