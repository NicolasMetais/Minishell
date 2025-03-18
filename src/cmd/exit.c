/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:19:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/18 02:15:15 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//EXIT DOIT AFFICHER DES ERREUR SI ON L'UTILISE MAL MAIS DOIT EXIT QUAND MEME
static void	free_exit(t_core *core, unsigned int status)
{
	free_global(core->glb, NULL);
	free_tab(core->splitted_path);
	kill_program(core);
	exit(status);
}

void	exit_custom(t_core *core, t_cmd *cmd, t_boolean fork)
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
	free_exit(core, status);
}
