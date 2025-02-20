/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:00:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/20 23:23:06 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE PRINT TOUTES LES VARS D'ENV
t_boolean	env(t_core *core, t_builtin *builtin)
{
	int	i;

	i = 0;
	if (builtin->arg_number > 1)
		return (false);
	while (core->env_dup[i])
	{
		if ((int)ft_strlen(core->env_dup[i]) <= 4096)
			printf("%s\n", core->env_dup[i]);
		else
		{
			ft_putendl_fd("/usr/bin/env: Argument list too long", 2);
			exit_code = 126;
			return (true);
		}
		i++;
	}
	return (true);
}
