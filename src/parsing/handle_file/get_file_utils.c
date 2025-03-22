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

char	**get_args(char **tmp, char **new, char ***tab)
{
	char	**old;

	old = new;
	new = realloc_add_to_tab(new, (*tmp));
	if (!new)
		return (free_split(old), free_split_get_fd(*tab), NULL);
	(*tmp) = NULL;
	if (ft_strlen(**tab) == 0)
	{
		free((**tab));
		(*tab)++;
	}
	while (*tab && **tab && ft_strlen(**tab) == 0)
	{
		(*tmp) = ft_strdup("");
		if (!(*tmp))
			return (free_split(new), free_split_get_fd(*tab), NULL);
		new = realloc_add_to_tab(new, (*tmp));
		if (!new)
			return (free_split(new), free_split_get_fd((*tab)), NULL);
		(*tmp) = NULL;
		free((**tab));
		(*tab)++;
	}
	return (new);
}

void	fd_var_init(char **tab, t_fd_var *var)
{
	var->head = tab;
	var->new = malloc(sizeof(char *));
	if (!var->new)
	{	
		free_split(tab);
		return ;
	}
	var->new[0] = NULL;
	var->tmp = NULL;
	var->current = NULL;
}

void	free_split_get_fd(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
}
