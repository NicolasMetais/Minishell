/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:00:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/07 04:31:10 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_var(t_core *core, t_builtin *builtin)
{
	int	i;

	(void)builtin;
	i = 0;
	core->line++;
	rotate_env(core, core->line);
	printf("%s\n", core->env->var);
}
