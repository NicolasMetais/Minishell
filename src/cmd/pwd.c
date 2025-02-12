/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:54:18 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/11 22:18:21 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	pwd(t_core *core, t_builtin *builtin)
{
	char	*pwd;

	if (builtin->arg_number > 1 && builtin->cmd[1][0] == '-')
	{
		if (ft_strcmp(builtin->cmd[1], "--") != 0)
			return (invalid_option(builtin, "pwd: "));
	}
	pwd = ft_get_env(core->env, "PWD");
	printf("%s\n", pwd);
	free(pwd);
	return (true);
}
