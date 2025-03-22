/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:09:30 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/22 11:53:45 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_file_free_and_incr(char ***tab)
{
	if (ft_strlen(**tab) == 0)
	{
		free((**tab));
		(*tab)++;
	}
}

t_boolean	get_file_check(char ***tab, t_red **current, char c, t_cmd *cmd)
{
	if ((*current)->type == double_)
		(**tab) = dynamic_delete(**tab);
	(**tab) = dynamic_delete(**tab);
	if ((*current)->empty_file)
		add_file_to_cmd("", c, cmd, *current);
	if ((*tab) && ft_strlen(**tab) == 0)
	{
		free((**tab));
		(*tab)++;
	}
	if ((*current)->empty_file)
	{
		free((**tab));
		(*tab)++;
		return (true);
	}
	return (false);
}

char	**get_args(char **tmp, char **new, char ***tab)
{
	new = realloc_add_to_tab(new, (*tmp));
	(*tmp) = NULL;
	if (ft_strlen(**tab) == 0)
	{
		free((**tab));
		(*tab)++;
	}
	while (*tab && **tab && ft_strlen(**tab) == 0)
	{
		new = realloc_add_to_tab(new, ft_strdup(""));
		free((**tab));
		(*tab)++;
	}
	return (new);
}

void	fd_var_init(char **tab, t_fd_var *var)
{
	var->providence = tab;
	var->new = malloc(sizeof(char *));
	var->new[0] = NULL;
	var->tmp = NULL;
	var->current = NULL;
}
