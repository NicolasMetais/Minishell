/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:00:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/10 11:07:13 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	env(t_core *core, t_builtin *builtin)
{
	int	i;

	i = 0;
	if (builtin->arg_number > 1)
		return (false);
	while (core->env_dup[i])
	{
		printf("%s\n", core->env_dup[i]);
		i++;
	}
	return (true);
}
