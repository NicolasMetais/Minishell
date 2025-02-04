/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:15:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/04 05:32:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_core *core, t_boolean undo)
{
	if (undo)
		core->env();
}

void	cd_exec(char *env_var, t_boolean undo)
{
	update_pwd(env_var, undo);
	chdir(env_var);
}

void	cd_parsing(t_core *core)
{
	while (*core->line != ' ')
		core->line++;
	core->line++;
	if (ft_strncmp(core->line, "~", 2) == 0)
		cd_exec(getenv("HOME"), false);
	if (ft_strncmp(core->line, "-", 2) == 0)
		cd_exec(getenv("OLDPWD"), true);
	if (chdir(core->line) == -1)
	{
		g_dollar_qmark = 2;
		perror("");
	}
}
