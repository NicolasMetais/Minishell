/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:07:28 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 20:12:57 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//READLINE (GNL) ON 0 (STDOUT) TO READ EVERY MINISHELL INPUT 
//READLINE LEAK DE BASE C MIEUX GNL MAIS IL EN FAUT UN PARFAIT BONUSE JE RECODERAIS CA UN DE CES JOURS
t_boolean	minishell_launch(char **av, char **env)
{
	char	*line;

	(void)av;
	(void)env;
	signal_handler();
	funny_stuff();
	while (1)
	{
		line = readline("minishell/ ");
		if (line)
			add_history(line);
		if ((ft_strncmp(line, "exit", 4) == 0))
			exit(42);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
		minishell_launch(av, env);
}
