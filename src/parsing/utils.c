/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 12:52:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-07 12:52:44 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Command_counter compte le nombre de commande stocke dans le char **line_split. 
La memoire de **line_split est allouee dans global_init() par ft_split(read_line, '|'). */

int	command_counter(char **line_split)
{
	int	i;

	i = 0;
	while (line_split[i])
		i++;
	return (i);
}