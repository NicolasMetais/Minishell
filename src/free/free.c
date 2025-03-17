/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:40:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 17:53:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FREE DE TOUT LE PROGRAMME
void	kill_program(t_core *core)
{
	close(core->save);
	close(core->save1);
	free(core->line);
	core->line = NULL;
	free(core->prompt);
	core->prompt = NULL;
	if (core->env)
		free_tab(core->env_dup);
	free_env(core);
}

void	free_random(t_exec *exec, t_core *core)
{
	free(core->path);
	core->path = NULL;
	free(exec->child_pid);
	exec->child_pid = NULL;
}

//FREE D'UN DOUBLE TABLEAU
void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}
