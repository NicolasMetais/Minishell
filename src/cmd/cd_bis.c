/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:32:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 15:48:44 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	cd_init_extend(t_core *core, t_cmd *cmd, t_gc *gc, t_cd *cd)
{
	if (cmd->args_nb > 2)
	{
		if (!too_many_args("cd: ", core))
			return (false);
		return (free_gc(gc), true);
	}
	if (ft_strcmp(cmd->args[1], "~") == 0 || cmd->args_nb == 1)
		cd->ishome = true;
	if (!cd_exec(core, cd, cmd, gc))
		return (free_gc(gc), false);
	return (true);
}

t_boolean	not_setted_check(t_core *core, t_gc *gc, t_cd *cd, char **folder)
{
	if (cd->ishome)
	{
		if (!cd->home)
		{
			if (!env_not_set("HOME", "cd: ", core))
				return (free_gc(gc), false);
		}
		*folder = cd->home;
	}
	if (cd->undo)
	{
		if (!cd->oldpwd)
		{
			if (env_not_set("OLDPWD", "cd: ", core))
				return (free_gc(gc), false);
		}

		*folder = cd->oldpwd;
	}
	return (true);
}
