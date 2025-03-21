/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:46:08 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/18 01:09:28 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//GESTION DU FLAG -N QUI PREND EN COMPTE LES MULTIPLE -N ET -NNNNN..
int	flag_check(t_cmd *cmd, t_boolean *flag)
{
	int	j;
	int	i;
	int	valid;

	i = 1;
	if (cmd->args_nb == 1)
		return (i);
	valid = 0;
	while (cmd->args[i]
		&& ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		j = 1;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] != 'n')
				return (i);
			j++;
		}
		valid++;
		*flag = true;
		i++;
	}
	return (i);
}

//PRINTF POUR EXEC ECHO
t_boolean	echo_init(t_cmd *cmd, t_core *core)
{
	int			i;
	t_boolean	flag;

	(void)core;
	flag = false;
	i = flag_check(cmd, &flag);
	while (cmd->args[i])
	{
		printf("%s ", cmd->args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (true);
}
