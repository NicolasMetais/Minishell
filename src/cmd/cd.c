/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:15:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 15:48:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE MET A JOUR PWD ET OLD AVEC LES BONNE PATH.
//OLDPWD A TOUJOURS UNE EXEC DE RETARD SUR PWD
t_boolean	update_pwd(t_core *core, t_cd *cd, t_gc *gc)
{
	char	*get_path;

	if (cd->pwd)
		cd->oldpwd = cd->pwd;
	rotate_env(core, "OLDPWD");
	free(core->env->var);
	core->env->var = ft_strjoin("OLDPWD=", cd->oldpwd);
	if (!core->env->var)
		return (false);
	rotate_env(core, "PWD");
	get_path = getcwd(NULL, 0);
	if (!get_path)
	{
		write(2, "chdir: error retrieving current directory: ", 43);
		perror("getcwd: cannot access parent directories");
		return (free_gc(gc), true);
	}
	free(core->env->var);
	core->env->var = ft_strjoin("PWD=", get_path);
	free(get_path);
	if (!core->env->var)
		return (false);
	if (update_env_dup(core) == 2)
		return (false);
	return (free_gc(gc), true);
}

//J'EXECUTE CD AVEC CHDIR ET L'ARGUMENT (folder) DEPEND DES OPTIONS
t_boolean	cd_exec(t_core *core, t_cd *cd, t_cmd *cmd, t_gc *gc)
{
	char	*folder;
	int		status;

	folder = cmd->args[1];
	if (!not_setted_check(core, gc, cd, &folder))
		return (false);
	status = chdir(folder);
	if (status < 0)
		return (funct_error("cd: ", folder, core));
	if (!update_pwd(core, cd, gc))
		return (false);
	return (true);
}

//AJOUTE UN ELEMENT A L'ENV
t_boolean	add_new_env(t_core *core, char *add)
{
	t_env	*new;
	t_env	*last;

	last = lstlast_env(core->env);
	new = new_env(add);
	if (!new)
		return (false);
	new->next = core->env;
	last->next = new;
	return (true);
}

//INIT D'UNE STRUCTURE AVEC PLEIN D'OPTIONS
t_boolean	cd_setup(t_core *core, t_cd *cd, t_gc **gc)
{
	*gc = NULL;
	cd->pwd = ft_get_env(core->env, "PWD");
	if (!cd->pwd)
	{
		if (!add_new_env(core, "PWD="))
			return (false);
	}
	add_to_gc(gc, cd->pwd);
	cd->oldpwd = ft_get_env(core->env, "OLDPWD");
	if (!cd->oldpwd)
	{
		if (!add_new_env(core, "OLDPWD="))
			return (free_gc(*gc), false);
	}
	add_to_gc(gc, cd->oldpwd);
	cd->home = ft_get_env(core->env, "HOME");
	add_to_gc(gc, cd->home);
	cd->undo = false;
	cd->ishome = false;
	return (true);
}

//JE REGARDE SI J'AI LES OPTIONS -, -- et ~ sinon je balance tout dans chdir
//JE CHECK LE NB d'ARG
t_boolean	cd_init(t_core *core, t_cmd *cmd)
{
	t_cd	cd;
	t_gc	*gc;

	if (!cd_setup(core, &cd, &gc))
		return (false);
	if (cmd->args_nb == 2)
	{
		if (cmd->args[1][0] == '-')
		{
			if (ft_strlen(cmd->args[1]) == 1)
				cd.undo = true;
			else if (cmd->args[1][1] == '-'
						&& ft_strlen(cmd->args[1]) == 2)
				cd.ishome = true;
			else
			{
				if (!invalid_option(cmd, "cd: ", core))
					return (false);
				return (free_gc(gc), true);
			}
		}
	}
	if (!cd_init_extend(core, cmd, gc, &cd))
		return (false);
	return (true);
}
