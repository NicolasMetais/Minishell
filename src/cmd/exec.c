/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:42:38 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/06 02:22:34 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec(t_core *core)
{
	char	**temp_arg;
	char	*slash;
	int		checker;
	char	*test;
	int		i;

	i = -1;
	if ((ft_strcmp(core->line, "exit") == 0))
		exit(0);
	temp_arg = ft_split(core->line, ' ');
	slash = ft_strjoin("/", temp_arg[0]);
	while (core->temp_path[++i])
	{
		test = ft_strjoin(core->temp_path[i], slash);
		checker = access(test, F_OK);
		if (checker == 0)
		{
			execve(test, temp_arg, core->env_dup);
			perror("");
		}
	}
}
