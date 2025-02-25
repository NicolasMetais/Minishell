/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 01:09:55 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/25 14:17:57 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//RETURN LA VAR D'ENV EN FONCTION DU NOM
char	*ft_get_env(t_env *env, char *name)
{
	t_env	*copy;
	int		size;
	int		i;
	char	*cut;

	if (!env || !name)
		return (NULL);
	i = -1;
	copy = env;
	size = ft_strlen(name);
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
