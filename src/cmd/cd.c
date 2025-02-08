/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:15:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 21:24:06 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief UPDATE TWO ENV VAR : PWD & OLDPWD TO KNOW 
 * THE SHELL POSITION IN THE FILES
 * @param core 
 * @param path 
 * @param undo 
 */
t_boolean	update_pwd(t_core *core, t_cd *cd, t_gc *gc)
{
	char	*get_path;

	cd->oldpwd = cd->pwd;
	rotate_env(core, "OLDPWD");
	free(core->env->var);
	core->env->var = ft_strjoin("OLDPWD=", cd->oldpwd);
	if (!core->env->var)
		return (false);
	rotate_env(core, "PWD");
	get_path = getcwd(NULL, 0);
	free(core->env->var);
	core->env->var = ft_strjoin("PWD=", get_path);
	free(get_path);
	if (!core->env->var)
		return (false);
	if (!update_env_dup(core))
		return (false);
	free_gc(gc);
	return (true);
}
/**
 * @brief EXEC CD WITH OPTIONS OR NOT / ERRORS
 * @param core 
 * @param path 
 * @param undo 
 */

t_boolean	cd_exec(t_core *core, t_cd *cd, t_builtin *builtin, t_gc *gc)
{
	char	*folder;
	int		status;

	folder = builtin->cmd[1];
	if (cd->ishome)
		folder = cd->home;
	if (cd->undo)
		folder = cd->oldpwd;
	status = chdir(folder);
	if (status == -1)
		return (funct_error("cd: ", folder));
	if (!update_pwd(core, cd, gc))
		return (false);
	return (true);
}

t_boolean	cd_setup(t_core *core, t_cd *cd, t_gc **gc)
{
	*gc = NULL;
	cd->pwd = ft_get_env(core->env, "PWD");
	if (!cd->pwd)
		return (false);
	add_to_gc(gc, cd->pwd);
	cd->oldpwd = ft_get_env(core->env, "OLDPWD");
	if (!cd->oldpwd)
		return (free_gc(*gc), false);
	add_to_gc(gc, cd->oldpwd);
	cd->home = ft_get_env(core->env, "HOME");
	if (!cd->home)
		return (free_gc(*gc), false);
	add_to_gc(gc, cd->home);
	cd->undo = false;
	cd->ishome = false;
	return (true);
}

/**
 * @brief check cd options -, --, ~ ,
 * arg numbers and invalid flags
 * @param core 
 */

t_boolean	cd_init(t_core *core, t_builtin *builtin)
{
	t_cd	cd;
	t_gc	*gc;

	if (!cd_setup(core, &cd, &gc))
		return (false);
	if (builtin->arg_number == 2)
	{
		if (builtin->cmd[1][0] == '-')
		{
			if (ft_strlen(builtin->cmd[1]) == 1)
				cd.undo = true;
			else if (builtin->cmd[1][1] == '-'
						&& ft_strlen(builtin->cmd[1]) == 2)
				cd.ishome = true;
			else
				return (invalid_option(builtin, "cd: "));
		}
	}
	if (builtin->arg_number > 2)
		return (too_many_args("cd: "));
	if (ft_strcmp(builtin->cmd[1], "~") == 0 || builtin->arg_number == 1)
		cd.ishome = true;
	if (!cd_exec(core, &cd, builtin, gc))
		return (false);
	return (true);
}
