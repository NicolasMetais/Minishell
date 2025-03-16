/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bis _bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 19:36:08 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-15 19:36:08 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	file_name_argument(char *cmd, t_core *core)
{
	char 	*custom_error;
	char	*tmp;

	tmp = ft_strjoin("minishell: ", cmd);
	if (!tmp)
		return (false);
	if (ft_strlen(cmd) == 1)
		custom_error = ft_strjoin(tmp, ": filename argument required");
	else
		custom_error = ft_strjoin(tmp, ": command not found");	
	free(tmp);
	if (!custom_error)
		return (false);
	ft_putendl_fd(custom_error, 2);
	if (ft_strlen(cmd) == 1)
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
	free(custom_error);
	if (ft_strlen(cmd) == 1)
		core->exit_code = 2;
	else
		core->exit_code = 127;
	return (true);
}
