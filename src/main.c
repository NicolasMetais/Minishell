/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/04 05:52:14 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 

void	core_init(t_core *core, int ac, char **av, char **env)
{
	int	i;

	i = -1;
	core->ac = ac;
	core->line = "\0";
	core->av = av;
	core->env = env;
	core->temp_path = ft_split(getenv("PATH"), ':');
	core->pwd = ft_strdup(getenv("PWD"));
	core->prompt = ft_strjoin(RED_LIGHT, core->pwd);
	core->prompt = ft_strjoin(core->prompt, "$ ");
	core->prompt = ft_strjoin(core->prompt, WHITE);
}
// -->/-->*-->*
/**
 * @brief
 * 
 * @param core 
 * @return t_boolean 
 */
t_boolean	minishell_launch(t_core *core)
{
	pid_t	pid;

	signal_handler();
	funny_stuff();
	while (1)
	{
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
		core_init(&core, ac, av, env);
		minishell_launch(&core);
	}
}
