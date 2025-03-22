/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:36:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/22 11:57:36 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_file_next_in_false(char ***tab, char **file, t_red **tab_red)
{
	if (is_redirection_char(***tab) && (*tab_red)->valid == false)
	{
		if ((*tab_red)->type == double_)
		{
			*file = dynamic_copy(*file, ***tab);
			(**tab) = dynamic_delete(**tab);
		}
		if ((*tab_red)->next)
			*tab_red = (*tab_red)->next;
	}
}

void	get_file(char ***tab, t_cmd *cmd, t_red **tab_red, t_red **current)
{
	t_get_file_var	var;

	var.c = ***tab;
	var.file = NULL;
	if (get_file_check(tab, current, var.c, cmd))
		return ;
	while (**tab && !(is_redirection_char(***tab) && (*tab_red)->valid == true))
	{
		get_file_next_in_false(tab, &var.file, tab_red);
		var.file = dynamic_copy(var.file, ***tab);
		(**tab) = dynamic_delete(**tab);
		if (((is_redirection_char(***tab) && (*tab_red)->valid == true)
				|| ft_strlen(**tab) == 0))
		{
			if (!var.file)
				break ;
			add_file_to_cmd(var.file, var.c, cmd, *current);
			free(var.file);
			var.file = NULL;
			get_file_free_and_incr(tab);
			break ;
		}
	}
}

char	*dynamic_incrementaton(char *tmp, char ***tab, t_red **tab_red)
{
	if (is_redirection_char(***tab) && (*tab_red)->valid == false)
	{	
		if ((*tab_red)->type == double_)
		{
			tmp = dynamic_copy(tmp, ***tab);
			(**tab) = dynamic_delete(**tab);
		}
		(*tab_red) = (*tab_red)->next;
	}
	tmp = dynamic_copy(tmp, ***tab);
	(**tab) = dynamic_delete(**tab);
	return (tmp);
}

char	**get_fd(char **tab, t_cmd	*cmd, t_red *tab_red)
{
	t_fd_var	var;

	fd_var_init(tab, &var);
	while (tab && *tab)
	{
		if (tab_red && is_redirection_char(**tab) && tab_red->valid == true)
		{
			var.current = tab_red;
			if (tab_red->next)
				tab_red = tab_red->next;
			get_file(&tab, cmd, &tab_red, &var.current);
			if (!tab || !*tab)
				break ;
			if (is_redirection_char(**tab) && tab_red->valid == true)
				continue ;
		}
		else
			var.tmp = dynamic_incrementaton(var.tmp, &tab, &tab_red);
		if ((ft_strlen(*tab) == 0 && var.tmp)
			|| (tab_red && is_redirection_char(**tab)
				&& tab_red->valid == true))
			var.new = get_args(&var.tmp, var.new, &tab);
	}
	return (free(var.providence), var.new);
}
