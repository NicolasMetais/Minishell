/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 03:47:20 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 15:01:50 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	update_env_dup(t_core *core)
{
	t_env	*copy;
	int		i;

	copy = core->env;
	i = 0;
	while (core->env->next != copy)
	{
		free(core->env_dup[i]);
		core->env_dup[i] = ft_strdup(core->env->var);
		if (!core->env_dup[i])
			return (false);
		core->env = core->env->next;
		i++;
	}
	return (true);
}
