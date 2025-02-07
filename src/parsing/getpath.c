/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 15:20:27 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-07 15:20:27 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_path(char **env)
{
	int		i;
	char	*s;
	char	**env_path;

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
	env_path = ft_split(s, ';');
	if (!env_path)
		return (NULL);
	return (env_path);
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
		j = 0;
		one_path = ft_strjoin(all_path[i], "/");
		while (cmd_line_split[j])
		{
			while (is_redirection(cmd_line_split[j]))
				j += 2;
			cmd_path = ft_strjoin(one_path, cmd_line_split[j]);
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (free(one_path), cmd_path);
			free(cmd_path);
			j++;
		}
		free(one_path);
		i++;
	}
	return (NULL);
}
