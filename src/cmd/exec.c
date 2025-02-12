/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:42:38 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/09 10:57:19 by nmetais          ###   ########.fr       */
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
	temp_arg = ft_split(core->line, ' ');
	if (!temp_arg)
		return ;
	slash = ft_strjoin("/", temp_arg[0]);
	if (!slash)
		return ;
	while (core->temp_path[++i])
	{
		test = ft_strjoin(core->temp_path[i], slash);
		checker = access(test, F_OK);
		if (checker == 0)
			execve(test, temp_arg, core->env_dup);
		else
			free(test);
	}
	test = ft_strjoin(temp_arg[0], ": ");
	cmd_not_found(test);
	free(test);
	free_tab(temp_arg);
	free(slash);
}
