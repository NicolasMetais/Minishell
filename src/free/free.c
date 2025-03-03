/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:40:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/25 14:29:29 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FREE DE TOUT LE PROGRAMME
void	kill_program(t_core *core)
{
	if (core->env)
		free_tab(core->env_dup);
	free_env(core);
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
		i++;
	}
	free(tab);
}
