/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:22:20 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/17 03:45:16 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(t_core *core)
{
	printf("exit\n");
	if (core->glb)
		free_global(core->glb);
	free_tab(core->splitted_path);
	kill_program(core);
	exit(0);
}

t_boolean	is_minishell(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp && tmp->args[0])
	{
		if (ft_strncmp(tmp->args[0], "./minishell", 11) == 0)
			i++;
		if (i > 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_boolean	main_setup(t_core *core, t_glb **global)
{
	add_history(core->line);
	*global = global_init(core);
	if (*global && (*global)->nb_cmd > 1 && is_minishell((*global)->cmd))
	{
		ft_putendl_fd("minishell : ./minishell in a pipe", 2);
		free_global(*global);
		*global = NULL;
	}
	core->glb = *global;
	return (true);
}

t_boolean	restore_stdio(t_core *core)
{
	if (dup2(core->save, STDIN_FILENO) < 0)
		return (false);
	if (dup2(core->save1, STDOUT_FILENO) < 0)
		return (false);
	return (true);
}
