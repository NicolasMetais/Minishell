/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:00:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 16:38:20 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE PRINT TOUTES LES VARS D'ENV
t_boolean	env(t_core *core, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->args_nb > 1)
		return (false);
	while (core->env_dup[++i])
	{
		if ((int)ft_strlen(core->env_dup[i]) > 4096)
		{
			ft_putendl_fd("/usr/bin/env: Argument list too long", 2);
			core->exit_code = 126;
			return (true);
		}
	}
	i = -1;
	while (core->env_dup[++i])
		printf("%s\n", core->env_dup[i]);
	return (true);
}
