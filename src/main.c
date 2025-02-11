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
//READLINE LEAK DE BASE C MIEUX GNL MAIS IL EN FAUT UN PARFAIT 
//BONUSE JE RECODERAIS CA UN DE CES JOURS
t_boolean	minishell_launch(char **av, char **env, t_glb *global)
{
	(void)av;
	char	*line;
	t_cmd	*tmp;
	int 	i;

	i = 0;
	tmp = NULL;
	while (1)
	{
		line = readline("minishell/ ");
		global = global_init(line, env);
		if (global)
			tmp = global->cmd;
		while (tmp)
		{
			printf("path = %s\n", tmp->path);
			printf("here_doc = %s\n", tmp->here_doc);
			printf("in_fd[0] (file descriptor) = %d\n", tmp->in_fd[0]);
			printf("in_fd[1] (redirection) = %d\n", tmp->in_fd[1]);
			printf("out_fd[0] (file descriptor) = %d\n", tmp->out_fd[0]);
			printf("out_fd[1] (redirection) = %d\n", tmp->out_fd[1]);
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

int	main(int ac, char **av, char **env)
{
	t_glb *global;

	global = NULL;
	if (ac == 1)
		minishell_launch(av, env, global);
}
