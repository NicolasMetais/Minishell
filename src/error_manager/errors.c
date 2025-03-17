/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:57:10 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 16:34:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TOUTES LES FONCTIONS D'ERREURS LEAK A CAUSE DES JOIN DE SES MORTS

//FLAG INVALIDE
t_boolean	invalid_option(t_cmd *cmd_tab, char *cmd, t_core *core)
{
	char	*custom_error;
	char	*wrong_str;
	char	*tmp;

	wrong_str = ft_substr(cmd_tab->args[1], 0, 2);
	if (!wrong_str)
		return (false);
	custom_error = ft_strjoin(cmd, wrong_str);
	free(wrong_str);
	if (!custom_error)
		return (false);
	tmp = ft_strjoin(custom_error, ": invalid option");
	free(custom_error);
	if (!tmp)
		return (false);
	custom_error = ft_strjoin("minishell: ", tmp);
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 2;
	return (true);
}

//TROP D'ARG
t_boolean	too_many_args(char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	custom_error = ft_strjoin(cmd, "too many arguments");
	if (!custom_error)
		return (false);
	tmp = ft_strjoin("minishell: ", custom_error);
	free(custom_error);
	if (!tmp)
		return (false);
	ft_putendl_fd(tmp, 2);
	free(tmp);
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
	perror("NINHO");
	free(custom_error);
	core->exit_code = 1;
	return (true);
}

//COMMAND NOT FOUND
t_boolean	cmd_not_found(char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd);
	if (!tmp)
		return (false);
	if (!is_a_file(cmd))
		custom_error = ft_strjoin(tmp, ": command not found");
	else
		custom_error = ft_strjoin(tmp, ": No such file or directory");
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 127;
	free(cmd);
	cmd = NULL;
	return (true);
}

int	only_num_arg(t_cmd *cmd_tab, char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	tmp = ft_strjoin(cmd_tab->args[1], ": numeric argument required");
	if (!tmp)
		return (false);
	custom_error = ft_strjoin(cmd, tmp);
	free(tmp);
	if (!custom_error)
		return (false);
	tmp = ft_strjoin("minishell: ", custom_error);
	free(custom_error);
	if (!tmp)
		return (false);
	ft_putendl_fd(tmp, 2);
	free(tmp);
	core->exit_code = 2;
	return (2);
}
