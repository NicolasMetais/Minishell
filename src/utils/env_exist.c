/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:00:27 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/18 02:10:24 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EST-CE QUE LA VAR D'ENV EXISTE
t_boolean	env_exist(t_core *core, char *var)
{
	t_env	*copy;

	if (!core->env || !var)
		return (false);
	copy = core->env;
	while (copy)
	{
		if (copy->name && ft_strcmp(copy->name, var) == 0)
			return (true);
		copy = copy->next;
		if (copy == core->env)
			break ;
	}
	return (false);
}
