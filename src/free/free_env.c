/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 04:58:13 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/20 18:02:11 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FREE PENDANT LA CREATION D'UN TAB
void	emergency_free_tab(char **tab, int i)
{
	while (tab[i])
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

//FREE PENDANT LA CREATION D'UNE LISTE CHAINEE
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

//FREE DE LA LISTE DE VAR MARQUEE
void	free_mark(t_core *core)
{
	t_env	*current;
	t_env	*next;
	int		i;
	int		size;

	if (!core->mark)
		return ;
	i = 0;
	current = core->mark;
	size = get_env_size(core->mark);
	while (i < size)
	{
		next = current->next;
		free(current->name);
		current->name = NULL;
		free(current->var);
		current->var = NULL;
		free(current);
		current = NULL;
		current = next;
		i++;
	}
}

//FREE DE LA VAR D'ENV
void	free_env(t_core *core)
{
	t_env	*current;
	t_env	*next;
	int		i;
	int		size;

	if (!core->env)
		return ;
	i = 0;
	current = core->env;
	size = get_env_size(core->env);
	while (i < size)
	{
		next = current->next;
		free(current->name);
		current->name = NULL;
		free(current->var);
		current->var = NULL;
		free(current);
		current = NULL;
		current = next;
		i++;
	}
	free_mark(core);
}
