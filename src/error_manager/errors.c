/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:57:10 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/09 18:32:52 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	invalid_option(t_builtin *builtin, char *cmd)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, ft_substr(builtin->cmd[1],
				0, 2));
	if (!custom_error)
		return (false);
	custom_error = ft_strjoin(custom_error, ": invalid option");
	if (!custom_error)
		return (free(custom_error), false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	exit_code = 2;
	return (true);
}

t_boolean	too_many_args(char *cmd)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, "too many arguments");
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	exit_code = 1;
	return (true);
}

t_boolean	funct_error(char *cmd, char *addvalue)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, addvalue);
	if (!custom_error)
		return (false);
	perror(custom_error);
	free(custom_error);
	exit_code = 1;
	return (true);
}

t_boolean	cmd_not_found(char *cmd)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, "command not found");
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	exit_code = 127;
	return (true);
}

int	only_num_arg(t_builtin *builtin, char *cmd)
{
	char	*custom_error;

	custom_error = ft_strjoin(builtin->cmd[1], ": numeric argument required");
	custom_error = ft_strjoin(cmd, custom_error);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	exit_code = 2;
	return (2);
}
