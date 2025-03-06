/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 22:34:42 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXIT DOIT AFFICHER DES ERREUR SI ON L'UTILISE MAL MAIS DOIT EXIT QUAND MEME
t_boolean	exit_custom(t_core *core, t_glb *global)
{
	unsigned int	status;
	int				i;

	i = 0;
	status = 0;
	printf("exit\n");
	if (global->cmd->args_nb > 1)
	{
		if ((global->cmd->args[1][0] == '-') || (global->cmd->args[1][0] == '+'))
			i++;
		while (global->cmd->args[1][i])
		{
			if (!ft_isdigit(global->cmd->args[1][i++]))
			{
				status = only_num_arg(global, "exit: ");
				break ;
			}
		}
		if (global->cmd->args_nb > 2 && !status)
			status = too_many_args("exit: ");
	}
	if (status == 0 && global->cmd->args_nb > 1)
		status = ft_atol(global->cmd->args[1]);
	kill_program(core);
	exit(status);
}
