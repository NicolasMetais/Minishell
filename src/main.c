/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/01 01:08:39 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 

void	core_init(t_core *core, int ac, char **av, char **env)
{
	core->ac = ac;
	core->av = av;
	core->env = env;
	core->dollars_qmark = 0;
}

t_boolean	minishell_launch(t_core *core)
{

	signal_handler();
	funny_stuff();
	while (1)
	{
		core->line = readline("minishell/ ");
		if (core->line)
			add_history(core->line);
		cmd_exec(core);
	}
}

int	main(int ac, char **av, char **env)
{
	t_core	core;

	if (ac == 1)
	{
		core_init(&core, ac, av, env);
		minishell_launch(&core);
	}
}
