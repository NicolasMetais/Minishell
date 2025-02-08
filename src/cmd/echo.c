/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 21:46:08 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 21:56:16 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	echo_init(t_builtin *builtin)
{
	if (builtin->arg_number == 2)
	{
		if (ft_strcmp(builtin->cmd[1], "$?") == 0)
			printf("%d", exit_code);
		else
			printf("%s", builtin->cmd[1]);
	}
	printf("\n");
	return (true);
}
