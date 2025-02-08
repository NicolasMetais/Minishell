/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 21:54:03 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	builtin_or_not(t_core *core, t_builtin *builtin)
{
	if ((ft_strcmp(builtin->cmd[0], "cd") == 0))
	{
		if (!cd_init(core, builtin))
		{
			printf("TEST\n");
			return (false);
		}
		return (true);
	}
	if ((ft_strcmp(builtin->cmd[0], "echo") == 0))
	{
		echo_init(builtin);
		return (true);
	}
	if ((ft_strcmp(core->line, "exit") == 0))
	{
		free_tab(core->env_dup);
		free_env(core);
		exit(0);
	}
/* 	if (builtin->cmd[0][0] == '$')
		return (env_var(core, &builtin), true); */
	return (false);
}

int	builtin(t_core *core)
{
	t_builtin	builtin;
	int			error;
	int			i;

	i = 0;
	builtin.cmd = ft_split(core->line, ' ');
	if (!builtin.cmd)
		return (2);
	while (builtin.cmd[i])
		i++;
	builtin.arg_number = i;
	error = builtin_or_not(core, &builtin);
	free_tab(builtin.cmd);
	return (error);
}
