/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-04 16:12:11 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-04 16:12:11 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_file(t_cmd *cmd, char **cmd_tab, t_red *tab_red)
{
	t_index	index;

	get_file_index_init(&index, cmd_tab);
	while (cmd_tab[index.i] && cmd_tab[index.i][index.j])
	{
		if (is_redirection_char(cmd_tab[index.i][index.j]) && tab_red->valid == false)
			if (get_file_increment_false(&index, cmd_tab, &tab_red))
				break ;
		if (is_redirection_char(cmd_tab[index.i][index.j]) && tab_red->valid == true)
		{
			cmd_tab = extract_file(cmd, cmd_tab, &tab_red, &index);
			if (!cmd_tab)
				return (NULL);
		}
		else
			index.j++;
		get_file_increment(&index, cmd_tab, &tab_red);
	}
	return (cmd_tab);
}

char	**get_fd(t_cmd *cmd, char **cmd_split, t_red *tab_red)
{
	t_red	*tmp;

	tmp = tab_red;
	cmd_split = get_file(cmd, cmd_split, tmp);
	if (!cmd_split)
		return	(free_fd(cmd->in, cmd->out), NULL);
	return (cmd_split);
}