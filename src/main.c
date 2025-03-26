/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/26 10:08:30 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

t_boolean	core_init(t_core *core, int ac, char **av)
{
	core->save1 = -1;
	core->save = -1;
	core->ac = ac;
	core->glb = NULL;
	core->av = av;
	core->pwd = NULL;
	core->prompt = NULL;
	core->new_line = NULL;
	core->errorno = 0;
	core->mark = NULL;
	core->exit_code = 0;
	core->line = NULL;
	if (!env_parse(core))
		return (false);
	core->splitted_path[0] += 5;
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
	core->prompt = ft_strjoin(LIGHT_BLUE, core->pwd);
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
	while (1)
	{
		sigint_exit_code(core, true);
		if (!prompt_update(core))
			core->prompt = NULL;
		free(core->line);
		core->line = readline(core->prompt);
		sigint_exit_code(core, false);
		g_signal = 0;
		if (!core->line && isatty(STDIN_FILENO))
			exit_program(core);
		else if (core->line && !empty(core->line))
		{
			if (!main_setup(core, &global))
				return (false);
			if (!global)
				continue ;
			if (!main_exec(global, core))
				return (false);
		}
		else if (ft_strlen(core->line) == 0)
			continue ;
		free_global(global, core);
	}
	return (true);
}

//DUPLICATION DE LA VARIABLE D'ENV
int	main(int ac, char **av, char **env)
{
	t_core	core;
	t_glb	*global;

	global = NULL;
	g_signal = 0;
	if (ac == 1)
	{
		signal_shell();
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
		if (!minishell_launch(&core, global))
			return (false);
	}
	else
		ft_putendl_fd("Too many args", 2);
}
