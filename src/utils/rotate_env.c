/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:50:52 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/20 22:30:34 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE ROTATE LA LISTE CHAINEE A L'ENDROIT INDIQUE

t_env	*rotate_env(t_core *core, char *var_name)
{
	t_env	*start;

	if (!core->env || !var_name)
		return (NULL);
	start = core->env;
	while (core->env)
	{
		if (ft_strcmp(core->env->name, var_name) == 0)
			return (core->env);
		core->env = core->env->next;
		if (core->env == start)
			break ;
	}
	return (core->env);
}
