/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 02:04:36 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/05 03:42:59 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	builtin(t_core *core)
{
 	if ((ft_strncmp(core->line, "cd", 2) == 0))
		return (cd_parsing(core), true);
	if (ft_strnstr(core->line, "echo $?", ft_strlen(core->line)))
		return (exit_status_display(core), true);
/* 	if ((ft_strncmp(core->line, "$", 1) == 0))
		return (env_var(core), true); */
	return (false);
}
