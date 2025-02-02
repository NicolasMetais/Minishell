/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:42:38 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/02 04:46:33 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec(t_core *core)
{
	if ((ft_strncmp(core->line, "exit", 4) == 0))
		exit(0);
	if ((ft_strncmp(core->line, "cd", 2) == 0))
		cd(core);
	if (ft_strnstr(core->line, "$?", ft_strlen(core->line)))
		exit_status_display(core);
	if ((ft_strncmp(core->line, "$", 1) == 0))
		env_var(core);
}
