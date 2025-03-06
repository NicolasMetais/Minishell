/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:54:18 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 22:42:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE PRINT LA VAR D'ENV PWD ET JE GERE LES OPTIONS -, --
t_boolean	pwd(t_glb *global)
{
	char	*pwd;

	if (global->cmd->args_nb > 1 && global->cmd->args[1][0] == '-')
	{
		if (ft_strcmp(global->cmd->args[1], "--") != 0)
			return (invalid_option(global, "pwd: "));
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (true);
}
