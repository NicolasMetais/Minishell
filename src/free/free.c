/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:40:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 23:33:41 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	core_close__here(t_core *core)
{
	int	n;

	n = 0;
	while (n < core->nb_pipe_here_doc)
	{
		close(core->pipe_here_doc[n][0]);
		close(core->pipe_here_doc[n][1]);
		n++;
	}
}

//FREE DE TOUT LE PROGRAMME
void	kill_program(t_core *core)
{
	if (core->save > 0)
		close(core->save);
	if (core->save1 > 0)
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
	free(exec->child_pid);
	core->splitted_path[0] -= 5;
	free_tab(core->splitted_path);
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
