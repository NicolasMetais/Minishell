/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-18 20:36:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-18 20:36:31 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ** char par char
// * string en string
//	*tab_red = (*tab_red)->next;

void	get_file(char ***tab, t_cmd *cmd, t_red **tab_red, t_red **current)
{
	char	c;
	char	*file;
	
	c = ***tab;
	file = NULL;
	if ((*current)->type == double_)
		(**tab) = dynamic_delete(**tab);
	(**tab) = dynamic_delete(**tab);
	if ((*tab) && ft_strlen(**tab) == 0)
	{
		free((**tab));
		(*tab)++;
	}
	while (**tab && !(is_redirection_char(***tab) && (*tab_red)->valid == true))
	{
		if (is_redirection_char(***tab) && (*tab_red)->valid == false)
		{
			if ((*tab_red)->next)
				*tab_red = (*tab_red)->next;
		}
		file = dynamic_copy(file, ***tab);
		(**tab) = dynamic_delete(**tab);
		if (((is_redirection_char(***tab) && (*tab_red)->valid == true) || ft_strlen(**tab) == 0))
		{
			if (!file)
				break ;
			add_file_to_cmd(file, c, cmd, *current);
			free(file);
			file = NULL;
			if (ft_strlen(**tab) == 0)
			{
				free((**tab));
				(*tab)++;
			}
			break ;
		}
	}
}

char	**get_fd(char **tab, t_cmd	*cmd, t_red *tab_red)
{
	char		**new;
	char		**providence;
	char		*tmp;
	t_red		*current;

	new = NULL;
	tmp = NULL;
	providence = tab;
	while (tab && *tab)
	{
		if (tab_red && is_redirection_char(**tab) && tab_red->valid == true)
		{
			current = tab_red;
			if (tab_red->next)
				tab_red = tab_red->next;
			get_file(&tab, cmd, &tab_red, &current);
			if (!tab || !*tab)
				break ;
			if (is_redirection_char(**tab) && tab_red->valid == true)
				continue ;
		}
		else
		{
			if (tab_red && is_redirection_char(**tab) && tab_red->valid == false)
				tab_red = tab_red->next;
			tmp = dynamic_copy(tmp, **tab);
			(*tab) = dynamic_delete(*tab);
		}
		if ((ft_strlen(*tab) == 0 && tmp) || (tab_red && is_redirection_char(**tab) && tab_red->valid == true))
		{
			new = realloc_add_to_tab(new, tmp);
			tmp = NULL;
			if (ft_strlen(*tab) == 0)
			{
				free(*tab);
				tab++;
			}
			while (tab && *tab && ft_strlen(*tab) == 0)
			{
				new = realloc_add_to_tab(new, ft_strdup(""));
				free(*tab);
				tab++;
			}
		}
	}
	return (free(providence), new);
}
