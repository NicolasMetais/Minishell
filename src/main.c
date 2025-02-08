/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/28 06:12:39 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 
//READLINE LEAK DE BASE C MIEUX GNL MAIS IL EN FAUT UN PARFAIT BONUSE JE RECODERAIS CA UN DE CES JOURS
t_boolean	minishell_launch(char **av, char **env, t_glb *global)
{
	(void)av;
	char	*line;

//	funny_stuff();
	while (1)
	{
		line = readline("minishell/ ");
		global_init(global, line, env);
		while (global->cmd)
		{
			printf("path = %s", global->cmd->path);
			printf("here_doc = %s", global->cmd->here_doc);
			printf("in_fd[0] (file descriptor) = %d", global->cmd->in_fd[0]);
			printf("in_fd[1] (redirection) = %d", global->cmd->in_fd[1]);
			printf("out_fd[0] (file descriptor) = %d", global->cmd->out_fd[0]);
			printf("out_fd[1] (redirection) = %d", global->cmd->out_fd[1]);
			global->cmd = global->cmd->next;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_glb *global;

	global = NULL;
	if (ac == 1)
		minishell_launch(av, env, global);
}
