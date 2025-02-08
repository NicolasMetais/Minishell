/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:57:10 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/08 21:51:41 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	invalid_option(t_builtin *builtin, char *cmd)
{
	char	*custom_error;

	custom_error = ft_strjoin(cmd, ft_substr(builtin->cmd[1],
				1, ft_strlen(builtin->cmd[1]) - 1));
	if (!custom_error)
		return (false);
	custom_error = ft_strjoin(custom_error, ": invalid option");
	if (!custom_error)
		return (free(custom_error), false);
	ft_putendl_fd(custom_error, 2);
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
	exit_code = 1;
	return (true);
}
