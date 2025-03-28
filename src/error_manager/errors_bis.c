/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:10:59 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 16:35:22 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ID INVALIDE
int	not_valid_id(char *arg, char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	custom_error = ft_strjoin(arg, ": not a valid identifier");
	if (!custom_error)
		return (false);
	tmp = ft_strjoin(cmd, custom_error);
	free(custom_error);
	if (!tmp)
		return (false);
	custom_error = ft_strjoin("minishell: ", tmp);
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 1;
	return (true);
}

int	env_not_set(char *arg, char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	custom_error = ft_strjoin(arg, " not set");
	if (!custom_error)
		return (false);
	tmp = ft_strjoin(cmd, custom_error);
	free(custom_error);
	if (!tmp)
		return (false);
	custom_error = ft_strjoin("minishell: ", tmp);
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 1;
	return (true);
}

t_boolean	permission_denied(char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd);
	if (!tmp)
		return (false);
	custom_error = ft_strjoin(tmp, ": permission denied");
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 126;
	return (true);
}

t_boolean	error_directory(char *cmd, t_core *core)
{
	char	*custom_error;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd);
	if (!tmp)
		return (false);
	custom_error = ft_strjoin(tmp, ": Is a directory");
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 126;
	free(cmd);
	cmd = NULL;
	return (true);
}
