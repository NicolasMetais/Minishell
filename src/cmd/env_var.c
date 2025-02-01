/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:00:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/01 05:53:59 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_var(t_core *core)
{
	int	i;

	i = 0;
	core->line++;
	while (core->env[i])
	{
		if (ft_strncmp(core->line, core->env[i], ft_strlen(core->line)) == 0)
		{
			core->line = core->line + ft_strlen(core->line);
		}
		i++;
	}
}
