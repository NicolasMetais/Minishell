/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/12 17:00:00 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	builtin_the_third(t_builtin *builtin, t_core *core)
{
	int i;

	i = 0;
	if ((ft_strcmp(builtin->cmd[0], "unset") == 0))
	{
		if (!exit_custom(core, builtin))
			return (false);
		return (true);
	}
	if ((builtin->cmd[0][0] == '_' || ft_isalpha(builtin->cmd[0][0])))
	{
		while (builtin->cmd[0][i])
		{
			if (builtin->cmd[0][i] == '=')
				printf("WIP: c'est une variable a assigner");
			i++;
		}
	}
	return (false);
}

t_boolean	builtin_the_sec(t_builtin *builtin, t_core *core)
{
	if ((ft_strcmp(builtin->cmd[0], "exit") == 0))
	{
		if (!exit_custom(core, builtin))
			return (false);
		return (true);
	}
	if ((ft_strcmp(builtin->cmd[0], "env") == 0))
	{
		if (!env(core, builtin))
			return (false);
		return (true);
	}
	if ((ft_strcmp(builtin->cmd[0], "export") == 0))
	{
		if (!export(core, builtin))
			return (false);
		return (true);
	}
	if ((ft_strcmp(builtin->cmd[0], "unset") == 0))
	{
		if (!exit_custom(core, builtin))
			return (false);
		return (true);
	}
	return (false);
}

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
		if (!echo_init(builtin))
			return (false);
		return (true);
	}
	if ((ft_strcmp(builtin->cmd[0], "pwd") == 0))
	{
		if (!pwd(core, builtin))
			return (false);
		return (true);
	}
	if (!builtin_the_sec(builtin, core))
		return (true);
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
 	if (!var_manager(core, &builtin))
		return (1);
	error = builtin_or_not(core, &builtin);
	free_tab(builtin.cmd);
	return (error);
}
