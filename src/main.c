/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/06 05:14:46 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 

void	core_init(t_core *core, int ac, char **av)
{
	int	i;
	i = -1;
	core->ac = ac;
	core->av = av;
	core->temp_path = ft_split(ft_get_env(core->env, "PATH"), ':');
}

void	prompt_update(t_core *core)
{
	core->pwd = ft_get_env(core->env, "PWD"); // peut etre un strdup ici mais jsp
	core->prompt = ft_strjoin(RED_LIGHT, core->pwd);
	core->prompt = ft_strjoin(core->prompt, "$ ");
	core->prompt = ft_strjoin(core->prompt, WHITE);
}

t_boolean	minishell_launch(t_core *core)
{
	pid_t	pid;

	signal_handler();
	funny_stuff();
	while (1)
	{
		prompt_update(core);
		core->line = readline(core->prompt);
		if (core->line)
		{
			add_history(core->line);
			if (!builtin(core))
			{
				pid = fork();
				if (pid == 0)
					cmd_exec(core);
				else
					wait(0);
			}
		}
	}
}


unsigned int	g_dollar_qmark = 0;

int	main(int ac, char **av, char **env)
{
	t_core			core;

	if (ac == 1)
	{
		duplicate_env(&core, env);
		core_init(&core, ac, av);
		minishell_launch(&core);
	}
}
