/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 17:45:14 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-09 17:45:14 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_cmd(char **all_path, char **cmd)
{
	char	*cmd_path;
	char	*one_path;
	int		i;
	int		j;

	i = 0;
	while (all_path[i])
	{
		j = 0;
		one_path = ft_strjoin(all_path[i], "/");
		if (!one_path)
			return (free(one_path), -2);
		while (cmd[j])
		{
			while (is_redirection(cmd[j]))
				j += 2;
			cmd_path = ft_strjoin(one_path, cmd[j]);
			if (!cmd_path)
				return (free(one_path), -2);
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (free(one_path), j);
			free(cmd_path);
			j++;
		}
		free(one_path);
		i++;
	}
	return (-1);
}

char	**get_cmd(char **cmd_line_split, char **all_path)
{
	char	**cmd;
	int		i_cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(char *) * (command_counter(cmd_line_split) + 1));
	if (!cmd)
		return (NULL);
	i_cmd = search_cmd(all_path, cmd_line_split);
	if (i_cmd == -1)
		return (cmd_line_split);
	if (i_cmd == -2)
		return (free(cmd), NULL);
	while (i < command_counter(cmd_line_split))
	{
		if (i == 0)
		{
			cmd[i] = ft_strdup(cmd_line_split[i_cmd]);
			if (!cmd[i])
				return (free_split_init(cmd, i), NULL);
			i++;
		}
		else if (i == i_cmd && i != 0)
			i++;
		else
		{
			cmd[i] = ft_strdup(cmd_line_split[i]);
			if (!cmd[i])
				return (free_split_init(cmd, i), NULL);
			i++;
		}
	}
	cmd[i] = NULL;
	return (cmd);
}
