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

/* u.s1 correspond a un des paths de $PATH, u.s2 correspond a u.s1/cmd  */
int	search_cmd(char **all_path, char **cmd)
{
	t_utils	u;

	u.i = 0;
	while (all_path[u.i])
	{
		u.j = 0;
		u.s1 = ft_strjoin(all_path[u.i], "/");
		if (!u.s1)
			return (free(u.s1), -2);
		while (cmd[u.j])
		{
			u.s2 = ft_strjoin(u.s1, cmd[u.j]);
			if (!u.s2)
				return (free(u.s1), -2);
			if (access(u.s2, F_OK | X_OK) == 0)
				return (free(u.s1), free(u.s2), u.j);
			free(u.s2);
			u.j++;
		}
		free(u.s1);
		u.i++;
	}
	return (-1);
}

char	**init_cmd(char **cmd_line_split, int i_cmd)
{
	char	**cmd;
	int		i;
	int		j;

	i = -1;
	j = 0;
	cmd = malloc(sizeof(char *) * (command_counter(cmd_line_split) + 1));
	if (!cmd)
		return (NULL);
	while (++i < command_counter(cmd_line_split))
	{
		if (i == 0)
		{
			cmd[i] = ft_strdup(cmd_line_split[i_cmd]);
			if (!cmd[i])
					return (free_split(cmd_line_split), free(cmd), NULL);
			i++;
		}
		if (j == i_cmd)
			j++;
		cmd[i] = ft_strdup(cmd_line_split[j]);
		if (!cmd[i])
			return (free_split(cmd_line_split), free_split_init(cmd, i), NULL);
		j++;
	}
	return (cmd);
}

char 	**one_word(char	**cmd_line_split)
{
	char	**cmd;
	cmd = malloc(sizeof(char *) * 2);
	if (!cmd)
		return (NULL);
	cmd[0] = ft_strdup(cmd_line_split[0]);
	if (!cmd[0])
		return (free(cmd), NULL);
	cmd[1] = NULL;
	return (cmd);
}

char	**get_cmd(char **cmd_line_split, char **all_path)
{
	char	**cmd;
	int		i_cmd;
	int		len;

	len = command_counter(cmd_line_split);
	if (len == 1)
	{
		cmd = one_word(cmd_line_split);
		if (!cmd)
			return (NULL);
		else 
			return (cmd);
	}
	i_cmd = search_cmd(all_path, cmd_line_split);
	if (i_cmd == -1)
		return (cmd_line_split);
	if (i_cmd == -2)
		return (NULL);
	cmd = init_cmd(cmd_line_split, i_cmd);
	if (!cmd)
		return (NULL);
	cmd[len] = NULL;
	return (cmd);
}
