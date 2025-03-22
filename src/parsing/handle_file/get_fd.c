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

char	*dynamic_incrementaton(char *tmp, char ***tab, t_red **tab_red)
{
	if (is_redirec_char(***tab) && (*tab_red)->valid == false)
	{	
		if ((*tab_red)->type == double_)
		{
			tmp = dynamic_copy(tmp, ***tab);
			if (!tmp)
				return (free_split(*tab), NULL);
			(**tab) = dynamic_delete(**tab);
			if (!**tab)
				return (dynamic_delete_failed(tab), free(tmp), NULL);
		}
		(*tab_red) = (*tab_red)->next;
	}
	tmp = dynamic_copy(tmp, ***tab);
	if (!tmp)
		return (free_split(*tab), NULL);
	(**tab) = dynamic_delete(**tab);
	if (!**tab)
		return (dynamic_delete_failed(tab), free(tmp), NULL);
	return (tmp);
}

void	get_fd_next_next(t_red *tab_red, t_fd_var *var, char ***tab)
{
	if ((ft_strlen(**tab) == 0 && var->tmp)
		|| (tab_red && is_redirec_char(***tab)
			&& tab_red->valid == true))
	{
		var->new = get_args(&var->tmp, var->new, tab);
		if (!var->new)
			free(var->head);
	}
}

t_boolean	get_fd_next(char ***tab, t_red **tab_red, t_fd_var *var, t_cmd *cmd)
{
	while (*tab && **tab)
	{
		if (*tab_red && is_redirec_char(***tab) && (*tab_red)->valid == true)
		{
			var->current = *tab_red;
			if ((*tab_red)->next)
				(*tab_red) = (*tab_red)->next;
			if (!get_file(tab, cmd, tab_red, &var->current))
				return (free_split(var->new),
					free(var->tmp), free(var->head), false);
			if (!*tab || !**tab)
				break ;
			if (is_redirec_char(***tab) && (*tab_red)->valid == true)
				continue ;
		}
		break ;
	}
	return (true);
}

char	**get_fd(char **tab, t_cmd	*cmd, t_red *tab_red)
{
	t_fd_var	var;

	fd_var_init(tab, &var);
	if (!var.new)
		return (NULL);
	while (tab && *tab)
	{
		if (tab_red && is_redirec_char(**tab) && tab_red->valid == true)
		{
			if (!get_fd_next(&tab, &tab_red, &var, cmd))
				return (NULL);
			if (!tab || !*tab)
				break ;
		}
		else
		{
			var.tmp = dynamic_incrementaton(var.tmp, &tab, &tab_red);
			if (!var.tmp)
				return (free_split(var.new), free(var.head), NULL);
		}
		get_fd_next_next(tab_red, &var, &tab);
		if (!var.new)
			return (NULL);
	}
	return (free(var.head), var.new);
}
