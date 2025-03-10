/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/10 18:56:46 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	core_init(t_core *core, int ac, char **av)
{
	int		i;

	i = -1;
	core->ac = ac;
	core->av = av;
	core->pwd = NULL;
	core->prompt = NULL;
	core->new_line = NULL;
	core->mark = NULL;
	core->exit_code = 0;
	return (true);
}

//UPDATE DE LA PATH DU SHELL
t_boolean	prompt_update(t_core *core)
{
	char	*temp;

	if (core->env)
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

int	empty(char *line)
{
	while (*line)
	{
		if (ft_isprint(*line))
			return (0);
		line++;
	}
	return (1);
}

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 
t_boolean	minishell_launch(t_core *core, t_glb *global)
{

	core->save = dup(STDIN_FILENO);
	funny_stuff();
	while (1)
	{
		signal_update();
		if (!prompt_update(core))
			core->prompt = NULL;
		core->line = readline(core->prompt);
		if (core->line && !empty(core->line))
		{
			add_history(core->line);
			if (!setup_var(core))
				return (false);
			global = global_init(core->line, core->env_dup); // IL FAUT RENOMMER TOUT ET METTRE CA DANS LA STRUCT CORE APRES MERGE
			if (!builtin(core, global))
				main_exec(global, core);
			if (dup2(core->save, STDIN_FILENO) < 0)
				return (false);
		}
		else if (!core->line)
		{
			printf("exit\n");
			kill_program(core);
			exit(0);
		}
		free_global(global);
		free(core->line);
	}
	return (true);
}

volatile sig_atomic_t	g_signal = 0;

//DUPLICATION DE LA VARIABLE D'ENV
int	main(int ac, char **av, char **env)
{
	t_core	core;
	t_glb	global;

	if (ac == 1)
	{
		if (env[0])
		{
			if (!duplicate_env(&core, env))
				return (false);
		}
		else
		{
			if (!create_empty_env(&core))
				return (false);
		}
		if (!core_init(&core, ac, av))
			return (free_env(&core), false);
		minishell_launch(&core, &global);
	}
	else
		printf("error\n");
}
