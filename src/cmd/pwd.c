/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:54:18 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 15:53:05 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE PRINT LA VAR D'ENV PWD ET JE GERE LES OPTIONS -, --
t_boolean	pwd(t_cmd *cmd, t_core *core)
{
	char	*pwd;

	if (cmd->args_nb > 1 && cmd->args[1][0] == '-')
	{
		if (ft_strcmp(cmd->args[1], "--") != 0)
		{
			return (invalid_option(cmd, "pwd: ", core));
		}

	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (false);
	printf("%s\n", pwd);
	free(pwd);
	return (true);
}
