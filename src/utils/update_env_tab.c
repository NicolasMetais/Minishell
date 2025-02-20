/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 03:47:20 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/19 16:26:18 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE LIT TOUT LA LISTE CHAINEE D'ENV ET J'UPDATE LE CHAR ** POUR EXECVE
t_boolean	update_env_dup(t_core *core)
{
	t_env	*copy;
	int		i;

	free_tab(core->env_dup);
	copy = core->env;
	i = 0;
	core->env_dup = malloc(sizeof(char *) * (get_env_size(core->env) + 1));
	if (!core->env)
		return (false);
	while (core->env->next != copy)
	{
		core->env_dup[i] = ft_strdup(core->env->var);
		if (!core->env_dup[i])
			return (false);
		core->env = core->env->next;
		i++;
	}
	core->env_dup[i] = NULL;
	return (true);
}
