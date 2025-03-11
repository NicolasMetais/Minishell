/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:57:10 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 16:46:42 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TOUTES LES FONCTIONS D'ERREURS LEAK A CAUSE DES JOIN DE SES MORTS

//FLAG INVALIDE
t_boolean	invalid_option(t_cmd *cmd_tab, char *cmd, t_core *core)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, ft_substr(cmd_tab->args[1],
				0, 2));
	if (!custom_error)
		return (false);
	custom_error = ft_strjoin(custom_error, ": invalid option");
	if (!custom_error)
		return (free(custom_error), false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 2;
	return (true);
}

//TROP D'ARG
t_boolean	too_many_args(char *cmd, t_core *core)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, "too many arguments");
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 1;
	return (true);
}

//PERROR MODULABLE
t_boolean	funct_error(char *cmd, char *addvalue, t_core *core)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, addvalue);
	if (!custom_error)
		return (false);
	perror(custom_error);
	free(custom_error);
	core->exit_code = 1;
	return (true);
}

//COMMAND NOT FOUND
t_boolean	cmd_not_found(char *cmd, t_core *core)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, "command not found");
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 127;
	return (true);
}

int	only_num_arg(t_cmd *cmd_tab, char *cmd, t_core *core)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd_tab->args[1], ": numeric argument required");
	custom_error = ft_strjoin(cmd, custom_error);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 2;
	return (2);
}
