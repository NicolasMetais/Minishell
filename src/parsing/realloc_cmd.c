/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-08 14:17:04 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-08 14:17:04 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_cmd(char **cmd, int supp)
{
	int		i;
	int		j;
	char	**cmd_dup;
	int		len;

	len = command_counter(cmd);
	cmd_dup = malloc(sizeof(char *) * len);
	if (!cmd_dup)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i == supp)
			j++;
		cmd_dup[i] = ft_strdup(cmd[j]); 
		if (!cmd_dup[i])
			return(free_split_init(cmd_dup, i), free_split(cmd), NULL);
		i++;
		j++;
	}
	free_split(cmd);
	cmd_dup[i] = NULL;
	return (cmd_dup);
}

t_boolean	realloc_fd_out(t_cmd *cmd, char **cmd_split, int i)	
{
	cmd->out_fd[0] = open_file(cmd_split[i + 1]);
	cmd_split = realloc_cmd(cmd_split, i + 1);
	if (!cmd_split)
		return (false);
	cmd->out_fd[0] = ft_strlen(cmd_split[i]);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (false);
}

t_boolean	realloc_fd_in(t_cmd *cmd, char **cmd_split, int i)
{
	cmd->in_fd[0] = open_file(cmd_split[i + 1]);
	cmd_split = realloc_cmd(cmd_split, i + 1);
	if (!cmd_split)
		return (false);
	cmd->in_fd[0] = ft_strlen(cmd_split[i]);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (false);
}
