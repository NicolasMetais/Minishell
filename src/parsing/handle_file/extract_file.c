/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:17:04 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/19 21:45:35 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_incr_tab_in_get_file(char ***tab)
{
	free((**tab));
	(*tab)++;
}

int	get_file_check(char ***tab, t_red **current, char c, t_cmd *cmd)
{
	if ((*current)->type == double_)
	{
		(**tab) = dynamic_delete(**tab);
		if (!**tab)
			return (dynamic_delete_failed(tab), -1);
	}
	(**tab) = dynamic_delete(**tab);
	if (!**tab)
		return (dynamic_delete_failed(tab), -1);
	if ((*current)->empty_file)
	{
		if (!add_file_to_cmd("", c, cmd, *current))
			return (free_split_get_fd(*tab), -1);
	}
	if ((*tab) && ft_strlen(**tab) == 0)
		free_incr_tab_in_get_file(tab);
	if ((*current)->empty_file)
	{
		free((**tab));
		(*tab)++;
		return (1);
	}
	return (0);
}

t_boolean	get_file_next(char ***tab, char **file, t_red **tab_red)
{
	if (is_redirec_char(***tab) && (*tab_red)->valid == false)
	{
		if ((*tab_red)->type == double_)
		{
			*file = dynamic_copy(*file, ***tab);
			if (!*file)
				return (free_split_get_fd(*tab), false);
			(**tab) = dynamic_delete(**tab);
			if (!**tab)
				return (dynamic_delete_failed(tab), free(*file), false);
		}
		if ((*tab_red)->next)
			*tab_red = (*tab_red)->next;
	}
	*file = dynamic_copy(*file, ***tab);
	if (!*file)
		return (free_split_get_fd(*tab), false);
	(**tab) = dynamic_delete(**tab);
	if (!**tab)
		return (dynamic_delete_failed(tab), free(*file), false);
	return (true);
}

void	f_var(t_get_file_var *var, t_cmd *cmd, t_red *current, char ***tab)
{
	var->c = ***tab;
	var->file = NULL;
	var->error = get_file_check(tab, &current, var->c, cmd);
}

t_boolean	get_file(char ***tab, t_cmd *cmd, t_red **tab_red, t_red **current)
{
	t_get_file_var	var;

	f_var(&var, cmd, *current, tab);
	if (var.error == 1)
		return (true);
	else if (var.error == -1)
		return (false);
	while (**tab && !(is_redirec_char(***tab) && (*tab_red)->valid == true))
	{
		if (!get_file_next(tab, &var.file, tab_red))
			return (false);
		if (((is_redirec_char(***tab) && (*tab_red)->valid == true)
				|| ft_strlen(**tab) == 0))
		{
			if (!var.file)
				break ;
			if (!add_file_to_cmd(var.file, var.c, cmd, *current))
				return (free_split_get_fd(*tab), free(var.file), false);
			free(var.file);
			var.file = NULL;
			get_file_free_and_incr(tab);
			break ;
		}
	}
	return (true);
}
