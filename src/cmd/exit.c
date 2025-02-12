/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/10 11:02:09 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	exit_custom(t_core *core, t_builtin *builtin)
{
	unsigned int	status;
	int				i;

	i = 0;
	status = 0;
	printf("exit\n");
	if (builtin->arg_number > 1)
	{
		if ((builtin->cmd[1][0] == '-') || (builtin->cmd[1][0] == '+'))
			i++;
		while (builtin->cmd[1][i])
		{
			if (!ft_isdigit(builtin->cmd[1][i++]))
			{
				status = only_num_arg(builtin, "exit: ");
				break ;
			}
		}
		if (builtin->arg_number > 2 && !status)
			status = too_many_args("exit: ");
	}
	if (status == 0 && builtin->arg_number > 1)
		status = ft_atol(builtin->cmd[1]);
	kill_program(core);
	exit(status);
}
