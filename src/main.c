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
t_boolean	minishell_launch(char **av, char **env)
{
	(void)av;
	(void)env;
	char	*line;
	funny_stuff();
	while (1)
	{
		line = readline("minishell/ ");
		
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac == 1)
		minishell_launch(av, env);
}
