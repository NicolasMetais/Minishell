/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 12:45:54 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-07 12:45:54 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int i;

	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_node(t_cmd *ctx)
{

}