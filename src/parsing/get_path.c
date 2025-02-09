/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 17:44:50 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-09 17:44:50 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_path(char **env)
{
	int		i;
	char	*s;
	char	**env_path;

	i = 0;
	s = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")) == 0)
		{
			s = env[i];
			break ;
		}
		i++;
	}
	s += 5;
	env_path = ft_split(s, ':');
	if (!env_path)
		return (NULL);
	return (env_path);
}

char	*handle_path_reshearching(char *one_path, char *cmd_line_split, int j)
{
	char	*cmd_path;

	cmd_path = ft_strjoin(one_path, cmd_line_split[j]);
	if (!cmd_path)
		return (free(one_path), NULL);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (free(one_path), cmd_path);
	return (cmd_path);
}

char	*get_path(char **cmd_line_split, char **all_path)
{
	char	*cmd_path;
	char	*one_path;
	int		i;
	int		j;

	i = 0;
	while (all_path[i])
	{
		one_path = ft_strjoin(all_path[i], "/");
		if (!one_path)
			return (NULL);
		j = -1;
		while (cmd_line_split[++j])
		{
			while (is_redirection(cmd_line_split[j]))
				j += 2;
			cmd_path = handle_path_reshearching(one_path, cmd_line_split, j);
			if (!cmd_path)
				return (NULL);
			free(cmd_path);
		}
		free(one_path);
		i++;
	}
	return (NULL);
}
