/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 03:47:20 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 15:26:31 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE LIT TOUT LA LISTE CHAINEE D'ENV ET J'UPDATE LE CHAR ** POUR EXECVE
int	update_env_dup(t_core *core)
{
	t_env	*copy;
	int		i;

	free_tab(core->env_dup);
	copy = core->env;
	i = 0;
	core->env_dup = malloc(sizeof(char *) * (get_env_size(core->env) + 1));
	if (!core->env)
		return (2);
	while (copy)
	{
		core->env_dup[i] = ft_strdup(core->env->var);
		if (!core->env_dup[i])
			return (2);
		core->env = core->env->next;
		i++;
		if (copy == core->env)
			break ;
	}
	core->env_dup[i] = NULL;
	return (true);
}
