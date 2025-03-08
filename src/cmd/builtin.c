/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 16:44:36 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//DEUXIEME CHECKER DE BUILTIN
t_boolean	builtin_the_sec(t_glb *global, t_core *core)
{
	if ((ft_strcmp(global->cmd->args[0], "exit") == 0))
	{
		if (!exit_custom(core, global))
			return (false);
		return (true);
	}
	if ((ft_strcmp(global->cmd->args[0], "env") == 0))
	{
		if (!env(core, global))
			return (false);
		return (true);
	}
	if ((ft_strcmp(global->cmd->args[0], "export") == 0))
	{
		if (!export(core, global))
			return (false);
		return (true);
	}
	if ((ft_strcmp(global->cmd->args[0], "unset") == 0))
	{
		if (!unset(core, global))
			return (false);
		return (true);
	}
	return (false);
}

//CHECKER DE BUILTIN
t_boolean	builtin_or_not(t_core *core, t_glb *global)
{
	if ((ft_strcmp(global->cmd->args[0], "cd") == 0))
	{
		if (!cd_init(core, global))
			return (false);
		return (true);
	}
	if ((ft_strcmp(global->cmd->args[0], "echo") == 0))
	{
		if (!echo_init(global))
			return (false);
		return (true);
	}
	if ((ft_strcmp(global->cmd->args[0], "pwd") == 0))
	{
		if (!pwd(global, core))
			return (false);
		return (true);
	}
	if (builtin_the_sec(global, core))
		return (true);
	return (false);
}

int	builtin(t_core *core, t_glb *global)
{
	int			error;
	int			i;

	i = 0;
	while (global->cmd->args[i])
		i++;
	global->cmd->args_nb = i;
	error = builtin_or_not(core, global);
	return (error);
}
