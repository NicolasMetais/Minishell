/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/07 09:31:15 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	builtin_or_not(t_core *core, t_builtin *builtin)
{
	if ((ft_strcmp(builtin->cmd[0], "cd") == 0))
	{
		if (!cd_init(core, builtin))
			return (false);
		return (true);
	}
	if ((ft_strcmp(builtin->cmd[0], "echo") == 0))
	{
		exit_status_display(core, builtin);
		return (true);
	}
	if ((ft_strcmp(core->line, "exit") == 0))
		exit(0);
/* 	if (builtin->cmd[0][0] == '$')
		return (env_var(core, &builtin), true); */
	return (false);
}

int	builtin(t_core *core)
{
	t_builtin	builtin;
	int			i;

	i = 0;
	builtin.cmd = ft_split(core->line, ' ');
	if (!builtin.cmd)
		return (2);
	while (builtin.cmd[i])
		i++;
	builtin.arg_number = i;
	if (builtin_or_not(core, &builtin))
		return (1);
	free_tab(builtin.cmd);
	return (0);
}
