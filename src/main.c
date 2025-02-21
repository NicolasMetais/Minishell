/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/21 18:25:10 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	core_init(t_core *core, int ac, char **av)
{
	int		i;
	char	*path;

	i = -1;
	core->ac = ac;
	core->av = av;
	core->pwd = NULL;
	core->prompt = NULL;
	core->new_line = NULL;
	core->mark = NULL;
	path = ft_get_env(core->env, "PATH");
	if (!path)
		return (false);
	core->temp_path = ft_split(path, ':');
	if (!core->temp_path)
		return (free(path), false);
	free(path);
	return (true);
}

//UPDATE DE LA PATH DU SHELL
t_boolean	prompt_update(t_core *core)
{
	char	*temp;

	free(core->prompt);
	core->pwd = ft_get_env(core->env, "PWD");
	if (!core->pwd)
		return (false);
	core->prompt = ft_strjoin(RED_LIGHT, core->pwd);
	free(core->pwd);
	if (!core->prompt)
		return (false);
	temp = ft_strjoin(core->prompt, "$ ");
	free(core->prompt);
	if (!temp)
		return (false);
	core->prompt = ft_strjoin(temp, WHITE);
	free(temp);
	if (!core->prompt)
		return (false);
	return (true);
}

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 
t_boolean	minishell_launch(t_core *core)
{
	pid_t	pid;
	int		error;

	signal_handler();
	funny_stuff();
	while (1)
	{
		if (!prompt_update(core))
			core->prompt = "Minishell/ ";
		core->line = readline(core->prompt);
		if (core->line)
		{
			add_history(core->line);
			if (!setup_var(core))
				return (false);
			error = builtin(core);
			if (error == 0)
			{
				pid = fork();
				if (pid == 0)
					cmd_exec(core);
				else
					wait(0);
			}
			else if (error == 2)
				kill_program(core);
		}
		else
		{
			printf("exit\n");
			kill_program(core);
			exit(0);
		}
		free_tab(core->new_line);
		free(core->line);
	}
}
//VAR GLOBALE EXIT
unsigned int	exit_code = 0;

//DUPLICATION DE LA VARIABLE D'ENV
int	main(int ac, char **av, char **env)
{
	t_core	core;

	if (ac == 1)
	{
		if (!duplicate_env(&core, env))
			return (false);
		if (!core_init(&core, ac, av))
			return (free_env(&core), false);
		minishell_launch(&core);
	}
	else
		printf("error\n");
}
