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
	if (len == 1)
		return (cmd);
	cmd_dup = malloc(sizeof(char *) * len);
	if (!cmd_dup)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < len - 1)
	{
		if (i == supp)
			j++;
		cmd_dup[i] = ft_strdup(cmd[j]);
		if (!cmd_dup[i])
			return (free_split_init(cmd_dup, i), free_split(cmd), NULL);
		j++;
	}
	free_split(cmd);
	cmd_dup[i] = NULL;
	return (cmd_dup);
}

char	**realloc_fd_out(t_cmd *cmd, char **cmd_split, int i)
{
	if (cmd->out_fd[0] > 0)
		close (cmd->out_fd[0]);
	cmd->out_fd[0] = open_file_out(cmd_split[i + 1], ft_strlen(cmd_split[i]));
	cmd->out_fd[1] = ft_strlen(cmd_split[i]);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (NULL);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (NULL);
	return (cmd_split);
}

char	**realloc_fd_in(t_cmd *cmd, char **cmd_split, int i)
{
	if (cmd->in_fd[0] > 0)
		close (cmd->in_fd[0]);
	cmd->in_fd[0] = open_file_in(cmd_split[i + 1]);
	cmd->in_fd[1] = ft_strlen(cmd_split[i]);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (NULL);
	cmd_split = realloc_cmd(cmd_split, i);
	if (!cmd_split)
		return (NULL);
	return (cmd_split);
}
