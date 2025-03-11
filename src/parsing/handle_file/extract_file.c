/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:37:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/10 22:57:20 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**simple_token(char **tab, t_index *index, t_red **tab_red, t_cmd *cmd)
{
	tab[index->i + 1] = handle_file_word_deux(tab[index->i][index->j], cmd,
			tab[index->i + 1], tab_red);
	if (!tab[index->i + 1])
		return (free_split(tab), free_end_tab(tab, index->i + 1), NULL);
	if (ft_strlen(tab[index->i + 1]) == 0)
	{
		tab = realloc_cmd(tab, index->i + 1);
		if (!tab)
			return (NULL);
		index->tab_len = command_counter(tab);
	}
	tab = realloc_cmd(tab, index->i);
	if (!tab)
		return (NULL);
	index->tab_len = command_counter(tab);
	return (tab);
}

char	**two_token(char **tab, t_index *index, t_red **tab_red, t_cmd *cmd)
{
	tab[index->i] = handle_cmd_file_word_un(cmd, tab[index->i], tab_red);
	if (!tab[index->i])
		return (free_split(tab), free_end_tab(tab, index->i), NULL);
	if (ft_strlen(tab[index->i]) == 0)
	{
		tab = realloc_cmd(tab, index->i);
		if (!tab)
			return (NULL);
		index->tab_len = command_counter(tab);
	}
	return (tab);
}

char	**three_token(char **tab, t_index *index, t_red **tab_red, t_cmd *cmd)
{
	t_red	*tmp;

	tmp = *tab_red;
	tab[index->i + 1] = handle_file_word_deux(tab[index->i][index->j],
			cmd, tab[index->i + 1], tab_red);
	if (!tab[index->i + 1])
		return (free_split(tab), free_end_tab(tab, index->i + 1), NULL);
	if (ft_strlen(tab[index->i + 1]) == 0)
	{
		tab = realloc_cmd(tab, index->i + 1);
		if (!tab)
			return (NULL);
		index->tab_len = command_counter(tab);
	}
	tab[index->i] = realloc_word_red_at_end(tab[index->i], tmp, -1);
	if (!tab[index->i])
		return (free_split(tab), free_end_tab(tab, index->i), NULL);
	return (tab);
}

char	**extract_file(t_cmd *cmd, char **tab, t_red **tab_red, t_index *index)
{
	if ((ft_strlen(tab[index->i]) == 1 && (*tab_red)->type == simple)
		|| (ft_strlen(tab[index->i]) == 2 && (*tab_red)->type == double_))
	{
		tab = simple_token(tab, index, tab_red, cmd);
		if (!tab)
			return (NULL);
	}
	else if ((tab[index->i][index->j + 1] != '\0' && (*tab_red)->type == simple)
		|| (tab[index->i][index->j + 1] != '\0'
			&& (tab[index->i][index->j + 2] != '\0'
				&& (*tab_red)->type == double_)))
	{
		tab = two_token(tab, index, tab_red, cmd);
		if (!tab)
			return (NULL);
	}
	else
	{
		tab = three_token(tab, index, tab_red, cmd);
		if (!tab)
			return (NULL);
	}
	index->j = 0;
	return (tab);
}
