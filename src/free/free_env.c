/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 04:58:13 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/07 05:40:52 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	emergency_free_tab(char **tab, int i)
{
	while (tab[i])
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	emergency_free_env_var(t_env *env)
{
	t_env	*copy;

	copy = env;
	while (copy)
	{
		env = env->next;
		free(copy);
		copy = env;
	}
}


void	free_env(t_core *core)
{
	t_env	*current;
	t_env	*next;
	int		i;
	int		size;

	i = 0;
	current = core->env;
	size = get_env_size(core->env);
	while (i < size)
	{
		next = current->next;
		free(current);
		current = next;
		i++;
	}
	free(core->env_dup);
}
