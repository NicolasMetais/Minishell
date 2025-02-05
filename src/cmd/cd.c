/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:15:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/05 07:02:05 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief CD READ AND UPDATE THE PWD AND OLDPWD VAR ENV WITH PARSING OPTIONS
 * @param core 
 * @param path 
 * @param undo 
 */
void	update_pwd(t_core *core, char *path, t_boolean undo)
{
	(void)undo;
	rotate_env(core, "OLDPWD");
	while (ft_strncmp(core->env->name, "OLDPWD", 6) != 0)
		core->env = core->env->next;
	core->env->env = ft_get_env(core->env, "PWD");
	while (ft_strncmp(core->env->name, "PWD", 3) != 0)
		core->env = core->env->next;
	core->env->env = ft_strjoin("PWD=", path);
}
/**
 * @brief SEEMS USELESS BUT I NEED IT FOR PROPER ERROR PRINTING
 * @param core 
 * @param path 
 * @param undo 
 */

void	cd_exec(t_core *core, char *path, t_boolean undo)
{
	if (chdir(path) == -1)
	{
		perror(ft_strjoin("cd: ", core->line));
		return ;
	}
	update_pwd(core, path, undo);
}
/**
 * @brief structure de pre-parsing
 * 
 * @param cd 
 * @param core 
 */

void	cd_init(t_cd *cd, t_core *core)
{ //FAUT CODER UN STRCMP PARCE QUE STRNCMP C CRINGE
	cd->pwd = ft_get_env(core->env, "PWD");
	cd->oldpwd = ft_get_env(core->env, "OLDPWD");
	cd->home = ft_get_env(core->env, "HOME");
	if (ft_strncmp(core->line, "-", 2))
		cd->undo = true;
	if (ft_strncmp(core->line, "~", 2) == 0)
		cd->ishome = true;
}
/**
 * @brief folder exist tests with chdir + exception managments 
 * TO-DO MANAGE SKIPPING PRINTABLE WITH A UTILS FUNCT AND 
 * CHECK FILES WITH AN ACCESS. I SHOULD CHDIR ONLY ONCE 
 * @param core 
 */

void	cd_parsing(t_core *core)
{
	t_cd	cd;

	cd_init(&cd, core);
	while (!isprint(*core->line) || *core->line == ' ')
		core->line++;
	core->line++;
	if (cd.home)
		return (cd_exec(core, ft_get_env(core->env, "HOME"), false), (void)0);
	else if (cd.undo)
		return (cd_exec(core, ft_get_env(core->env, "OLDPWD"), true), (void)0);
	cd_exec(core, core->line, false);
}
