/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 19:32:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-17 19:32:56 by jbayonne         ###   ########.fr       */
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
