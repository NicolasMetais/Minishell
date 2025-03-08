/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-07 22:58:14 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-07 22:58:14 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// FREE LISTE FD
void	free_list_fd(t_file *cmd)
{
	t_file	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->file);
		free(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}

void	free_fd(t_file *in, t_file *out)
{
	if (in)
		free_list_fd(in);
	if (out)
		free_list_fd(out);
}

void free_end_tab(char **cmd_tab, int i)
{
	i++;
	while (cmd_tab[i])
	{
		free(cmd_tab[i]);
		i++;
	}
}

void	free_tab_red(t_red *cmd)
{
	t_red	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}