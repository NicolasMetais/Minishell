/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:15:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/01 01:12:29 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_core *core)
{
	while (*core->line != ' ')
		core->line++;
	core->line++;
	if (chdir(core->line) == -1)
	{
		core->dollars_qmark = 2;
		perror("");
	}
}
