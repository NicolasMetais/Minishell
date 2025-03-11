/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:10:59 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/08 16:47:28 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ID INVALIDE
int	not_valid_id(char *arg, char *cmd, t_core *core)
{
	char	*custom_error;

	custom_error = ft_strjoin(arg, ": not a valid identifier");
	custom_error = ft_strjoin(cmd, custom_error);
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

	custom_error = ft_strjoin(arg, " not set");
	custom_error = ft_strjoin(cmd, custom_error);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	free(custom_error);
	core->exit_code = 1;
	return (true);
}
