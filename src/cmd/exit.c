/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 16:02:33 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	overflow_long(char *args)
{
	if (ft_atol(args) == LONG_MAX || ft_atol(args) == LONG_MIN)
		return (true);
	return (false);
}

void	free_exit(t_core *core, unsigned int status)
{
	free_global(core->glb, NULL);
	core->splitted_path[0] -= 5;
	free_tab(core->splitted_path);
	kill_program(core);
	exit(status);
}

t_boolean	num_arg(t_cmd *cmd, int *i, t_core *core, int *status)
{
	while (cmd->args[1][*i])
	{
		if (!ft_isdigit(cmd->args[1][*i]) || overflow_long(cmd->args[1]))
		{
			if (!only_num_arg(cmd, "exit: ", core))
				return (false);
			*status = 2;
			break ;
		}
		(*i)++;
	}
	return (true);
}

t_boolean	exit_custom(t_core *core, t_cmd *cmd, t_boolean fork)
{
	unsigned int	status;
	int				i;

	i = 0;
	status = 0;
	if (fork == 0)
		printf("exit\n");
	if (cmd->args_nb > 1)
	{
		if ((cmd->args[1][0] == '-') || (cmd->args[1][0] == '+'))
			i++;

		if (cmd->args_nb > 2 && !status)
		{
			if (!too_many_args("exit: ", core))
				return (false);
			return (true);
		}
	}
	if (status == 0 && cmd->args_nb > 1)
		status = ft_atol(cmd->args[1]);
	free_exit(core, status);
	return (true);
}
