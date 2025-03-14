/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:51:02 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/13 16:27:11 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(t_core *core)
{
	printf("exit\n");
	kill_program(core);
	exit(0);
}

t_boolean	main_setup(t_core *core, t_glb **global)
{
	add_history(core->line);
	if (!expansion_var(core))
		return (false);
	*global = global_init(core);
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
