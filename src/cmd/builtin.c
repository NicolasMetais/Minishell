/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/06 05:13:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	builtin(t_core *core)
{
	t_builtin	builtin;
	int			i;

	i = 0;
	builtin.cmd = ft_split(core->line, ' ');
	while (builtin.cmd[i])
		i++;
	builtin.arg_number = i;
	if ((ft_strcmp(builtin.cmd[0], "cd") == 0))
		return (cd_init(core, &builtin), true);
	if ((ft_strcmp(builtin.cmd[0], "echo") == 0))
		return (exit_status_display(core, &builtin), true);
/* 	if (builtin.cmd[0][0] == '$')
		return (env_var(core, &builtin), true); */
	return (false);
}
