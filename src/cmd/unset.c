/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:36:19 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/19 22:09:55 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//P'TI DELETE
void	delete_env(t_core *core)
{
	t_env	*last;
	t_env	*next;

	last = lstlast_env(core->env);
	if (get_env_size(core->env) == 1)
	{
		free(core->env->name);
		free(core->env->var);
		free(core->env);
		core->env = NULL;
		return ;
	}
	next = core->env->next;
	free(core->env->name);
	free(core->env->var);
	free(core->env);
	core->env = next;
	last->next = next;
	return ;
}
//JE VAIS CHERCHER LA VAR D'ENV ET JE LA DELETE SI ELLE EXISTE
//NOT A VALID IDENTIFIER
t_boolean	unset(t_core *core, t_builtin *builtin)
{
	int	i;

	i = 0;
	if (builtin->arg_number > 1)
	{
		while (builtin->cmd[++i])
		{
			if (env_exist(core, builtin->cmd[i]))
			{
				rotate_env(core, builtin->cmd[i]);
				delete_env(core);
				update_env_dup(core);
			}
		}
	}
	return (true);
}
