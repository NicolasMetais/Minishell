/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 16:42:21 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXIT DOIT AFFICHER DES ERREUR SI ON L'UTILISE MAL MAIS DOIT EXIT QUAND MEME
t_boolean	exit_custom(t_core *core, t_cmd *cmd)
{
	unsigned int	status;
	int				i;

	i = 0;
	status = 0;
	printf("exit\n");
	if (cmd->args_nb > 1)
	{
		if ((cmd->args[1][0] == '-') || (cmd->args[1][0] == '+'))
			i++;
		while (cmd->args[1][i])
		{
			if (!ft_isdigit(cmd->args[1][i++]))
			{
				status = only_num_arg(cmd, "exit: ", core);
				break ;
			}
		}
		if (cmd->args_nb > 2 && !status)
			status = too_many_args("exit: ", core);
	}
	if (status == 0 && cmd->args_nb > 1)
		status = ft_atol(cmd->args[1]);
	kill_program(core);
	exit(status);
}
