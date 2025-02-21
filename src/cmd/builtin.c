/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/21 18:24:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//DEUXIEME CHECKER DE BUILTIN
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
		if (!unset(core, builtin))
			return (false);
		return (true);
	}
	return (false);
}

//CHECKER DE BUILTIN
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
	if (builtin_the_sec(builtin, core))
		return (true);
	return (false);
}

//JE DECOUPE LES ARGS ENTRE LES PIPES 
//(echo test | ls -l) (je decoupe echo test pour trouver echo)
int	builtin(t_core *core)
{
	t_builtin	builtin;
	int			error;
	int			i;

	i = 0;
	while (core->new_line[i])
		i++;
	builtin.arg_number = i;
	builtin.cmd = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (core->new_line[++i])
		builtin.cmd[i] = ft_strdup(core->new_line[i]);
	builtin.cmd[i] = NULL;
	exit_code = 0;
	error = builtin_or_not(core, &builtin);
	free_tab(builtin.cmd);
	return (error);
}
