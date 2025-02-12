/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:46:08 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/09 13:23:49 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_check(t_builtin *builtin, t_boolean *flag)
{
	int	j;
	int	i;
	int	valid;

	i = 1;
	if (builtin->arg_number == 1)
		return (i);
	valid = 0;
	while (builtin->cmd[i] && ft_strncmp(builtin->cmd[i], "-n", 2) == 0)
	{
		j = 1;
		while (builtin->cmd[i][j])
		{
			if (builtin->cmd[i][j] != 'n')
				return (i);
			j++;
		}
		valid++;
		*flag = true;
		i++;
	}
	return (i);
}

t_boolean	echo_init(t_builtin *builtin)
{
	int			i;
	t_boolean	flag;

	flag = false;
	i = flag_check(builtin, &flag);
	while (builtin->cmd[i])
	{
		printf("%s ", builtin->cmd[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (true);
}
