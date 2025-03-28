/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/26 11:51:59 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_builtin(t_cmd *cmd)
{
	if ((ft_strcmp(cmd->args[0], "cd") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "echo") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "pwd") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "exit") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "env") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "export") == 0))
		return (true);
	if ((ft_strcmp(cmd->args[0], "unset") == 0))
		return (true);
	return (false);
}

//DEUXIEME CHECKER DE BUILTIN
t_boolean	builtin_the_sec(t_cmd *cmd, t_core *core, t_boolean fork
	, t_exec *exec)
{
	if ((ft_strcmp(cmd->args[0], "exit") == 0))
	{
		exit_custom(core, cmd, fork, exec);
		return (true);
	}
	if ((ft_strcmp(cmd->args[0], "env") == 0))
	{
		if (!env(core, cmd))
			return (false);
		return (true);
	}
	if ((ft_strcmp(cmd->args[0], "export") == 0))
	{
		if (!export(core, cmd))
			return (false);
		return (true);
	}
	if ((ft_strcmp(cmd->args[0], "unset") == 0))
	{
		if (!unset(core, cmd))
			return (false);
		return (true);
	}
	return (false);
}

//CHECKER DE BUILTIN
t_boolean	builtin_or_not(t_core *core, t_cmd *cmd, t_boolean fork
		, t_exec *exec)
{
	if ((ft_strcmp(cmd->args[0], "cd") == 0))
	{
		if (!cd_init(core, cmd))
			return (false);
		return (true);
	}
	if ((ft_strcmp(cmd->args[0], "echo") == 0))
	{
		if (!echo_init(cmd, core))
			return (false);
		return (true);
	}
	if ((ft_strcmp(cmd->args[0], "pwd") == 0))
	{
		if (!pwd(cmd, core))
			return (false);
		return (true);
	}
	if (builtin_the_sec(cmd, core, fork, exec))
		return (true);
	return (false);
}

int	builtin(t_core *core, t_cmd *cmd, t_boolean fork, t_exec *exec)
{
	t_boolean	error;
	int			i;

	i = 0;
	error = false;
	while (cmd->args[i])
		i++;
	cmd->args_nb = i;
	if (is_builtin(cmd))
		error = builtin_or_not(core, cmd, fork, exec);
	return (error);
}
