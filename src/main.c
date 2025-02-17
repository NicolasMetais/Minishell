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

t_boolean	minishell_launch(char **av, char **env, t_glb *global)
{
	(void)av;
	char	*line;
	t_cmd	*tmp;
	int 	i;

	i = 0;
	tmp = NULL;
	while (i < 2)
	{
		line = readline("minishell/ ");
		global = global_init(line, env);
		if (global)
			tmp = global->cmd;
		while (tmp)
		{
			if (tmp->here_doc)
			{
				for (int i = 0; tmp->here_doc[i]; i++)
					printf("here_doc[%d] = %s\n", i, tmp->here_doc[i]);
			}
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
