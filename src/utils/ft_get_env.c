/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:09:55 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/12 22:20:21 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Get env content from env name
 * 
 * @param env 
 * @param name 
 * @return char* 
 */
char	*ft_get_env(t_env *env, char *name)
{
	t_env	*copy;
	int		size;
	int		i;
	char	*cut;

	if (!env || !name)
		return (NULL);
	i = -1;
	size = ft_strlen(name);
	copy = env;
	while (1)
	{
		if (copy->name && copy->var && ft_strncmp(copy->name, name, size) == 0
			&& ft_strlen(copy->var) > (size_t)size && copy->var[size] == '=')
		{
			cut = ft_substr(copy->var, size + 1, ft_strlen(copy->var));
			return (cut);
		}
		copy = copy->next;
		if (copy == env)
			break ;
	}
	return (NULL);
}
