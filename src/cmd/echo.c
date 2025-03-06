/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:46:08 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 22:42:13 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//GESTION DU FLAG -N QUI PREND EN COMPTE LES MULTIPLE -N ET -NNNNN..
int	flag_check(t_glb *global, t_boolean *flag)
{
	int	j;
	int	i;
	int	valid;

	i = 1;
	if (global->cmd->args_nb == 1)
		return (i);
	valid = 0;
	while (global->cmd->args[i]
		&& ft_strncmp(global->cmd->args[i], "-n", 2) == 0)
	{
		j = 1;
		while (global->cmd->args[i][j])
		{
			if (global->cmd->args[i][j] != 'n')
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
t_boolean	echo_init(t_glb *global)
{
	int			i;
	t_boolean	flag;

	flag = false;
	i = flag_check(global, &flag);
	while (global->cmd->args[i])
	{
		printf("%s ", global->cmd->args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (true);
}
