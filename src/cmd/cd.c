/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 23:15:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/06 06:41:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*check_for_env(t_core *core, char *folder)
// {
// 	int	i;
// 	int j;

// 	i = 0; //FAUT RECODER CA PLUS HAUT CA MARCHE PARTOUT PAREIL :)
// 	while (folder[i])
// 	{
// 		if (folder[i] == '$')
// 		{
// 			j = i + 1;
// 			while (folder[j])
// 			{
// 				if (!ft_isalpha(folder[j]))
// 				{
// 					if (ft_get_env(core->env, ft_substr(folder, i + 1, j)))
// 					{
// 						insert_in_folder(folder, i, j);
// 					}
// 				}
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// }

/**
 * @brief UPDATE TWO ENV VAR : PWD & OLDPWD TO KNOW 
 * THE SHELL POSITION IN THE FILES
 * @param core 
 * @param path 
 * @param undo 
 */
void	update_pwd(t_core *core, t_cd *cd)
{

	cd->oldpwd = cd->pwd;
	rotate_env(core, "OLDPWD");
	core->env->env = ft_strjoin("OLDPWD=", cd->oldpwd);
	rotate_env(core, "PWD");
	core->env->env = ft_strjoin("PWD=", getcwd(NULL, 0));
}
/**
 * @brief EXEC CD WITH OPTIONS OR NOT / ERRORS
 * @param core 
 * @param path 
 * @param undo 
 */

void	cd_exec(t_core *core, t_cd *cd, t_builtin *builtin)
{
	char	*folder;
	int		status;

	folder = builtin->cmd[1];
	if (cd->ignore)
		folder = builtin->cmd[2];
	if (cd->ishome)
		folder = ft_get_env(core->env, "HOME");
	if (cd->undo)
		folder = ft_get_env(core->env, "OLDPWD");
	status = chdir(folder);
	if (status == -1)
	{
		perror(ft_strjoin("cd: ", folder));
		return ;
	}
	update_pwd(core, cd);
}

/**
 * @brief check cd options -, --, ~ ,
 * arg numbers and invalid flags
 * @param core 
 */

void	cd_init(t_core *core, t_builtin *builtin)
{
	t_cd	cd;
	int		i;
	char	*custom_error;

	i = 0;
	cd.pwd = ft_get_env(core->env, "PWD");
	cd.oldpwd = ft_get_env(core->env, "OLDPWD");
	cd.home = ft_get_env(core->env, "HOME");   
	cd.undo = false;
	cd.ishome = false;
	cd.ignore = false;
	if (builtin->cmd[1][0] == '-')
	{
		if (builtin->arg_number == 2)
			cd.undo = true;
		if (builtin->cmd[1][1] == '-' && builtin->arg_number == 3)
			cd.ignore = true;
		else
		{ //a mettre dans un error_manager pour la norme ?
			custom_error = ft_strjoin("cd: ", ft_substr(builtin->cmd[1],
						1, ft_strlen(builtin->cmd[1]) - 1));
			custom_error = ft_strjoin(custom_error, ": invalid option");
			ft_putendl_fd(custom_error, 2);
			g_dollar_qmark = 2;
			return ;
		}
	}
	if (ft_strcmp(builtin->cmd[1], "~") == 0 || builtin->arg_number == 1)
		cd.ishome = true;
	if (builtin->arg_number > 2)
	{
		g_dollar_qmark = 2;
		ft_putendl_fd("cd: too many arguments", 2);
		return ;
	}
	cd_exec(core, &cd, builtin);
}
