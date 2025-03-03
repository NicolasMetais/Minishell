/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 17:26:02 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	minishell_launch(char **av, char **env, t_glb *global)
{
	(void)av;
	char	*line;
	t_cmd	*tmp;
	int 	i;

	i = 0;
	tmp = NULL;
	while (i < 1)
	{
		line = readline("minishell/ ");
		global = global_init(line, env);
		if (global)
			tmp = global->cmd;
		while (tmp)
		{
			// if (tmp->here_doc)
			// {
			// 	for (int i = 0; tmp->here_doc[i]; i++)
			// 		printf("here_doc[%d] = %s\n", i, tmp->here_doc[i]);
			// }
			// printf("in_fd[0] (file descriptor) = %d\n", tmp->in_fd[0]);
			// printf("in_fd[1] (redirection) = %d\n", tmp->in_fd[1]);
			// printf("out_fd[0] (file descriptor) = %d\n", tmp->out_fd[0]);
			// printf("out_fd[1] (redirection) = %d\n", tmp->out_fd[1]);
			 for (int i = 0; tmp->cmd[i]; i++)
			 	printf("%s \n", tmp->cmd[i]);
			 tmp = tmp->next;
		}
		i++;
		free(line);
		free_global(global);
	}
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

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 
t_boolean	minishell_launch(t_core *core)
{
	pid_t	pid;
	int		error;

	funny_stuff();
	while (1)
	{
		if (!prompt_update(core))
			core->prompt = NULL;
		signal_update();
		core->line = readline(core->prompt);
		if (core->line)
		{
			if (!setup_var(core))
				return (false);
			add_history(core->line);
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

	core.env = NULL;
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
		minishell_launch(&core);
	}
	else
		printf("error\n");
}
