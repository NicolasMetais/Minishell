/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file. c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-08 12:37:55 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-08 12:37:55 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**simple_token(char **cmd_tab, t_index *index, t_red **tab_red, t_cmd *cmd)
{
	cmd_tab[index->i + 1] = handle_cmd_file_word_deux(cmd_tab[index->i][index->j], cmd, cmd_tab[index->i + 1], tab_red);
	if (!cmd_tab[index->i + 1])
		return (free_split(cmd_tab), free_end_tab(cmd_tab, index->i + 1), NULL);
	if (ft_strlen(cmd_tab[index->i + 1]) == 0)
	{
		cmd_tab = realloc_cmd(cmd_tab, index->i + 1);
		if (!cmd_tab)
			return (NULL);
		index->tab_len = command_counter(cmd_tab);
	}
	cmd_tab = realloc_cmd(cmd_tab, index->i);
	if (!cmd_tab)
		return (NULL);
	index->tab_len = command_counter(cmd_tab);
	return (cmd_tab);
}

char	**two_token_in_one_word(char **cmd_tab, t_index *index, t_red **tab_red, t_cmd *cmd)
{
	cmd_tab[index->i] = handle_cmd_file_word_un(cmd, cmd_tab[index->i], tab_red);
	if (!cmd_tab[index->i])
		return (free_split(cmd_tab), free_end_tab(cmd_tab, index->i), NULL);				
	if (ft_strlen(cmd_tab[index->i]) == 0)
	{
		cmd_tab = realloc_cmd(cmd_tab, index->i);
		if (!cmd_tab)
			return (NULL);
		index->tab_len = command_counter(cmd_tab);
	}
	return (cmd_tab);
}

char	**three_token_in_two_word(char **cmd_tab, t_index *index, t_red **tab_red, t_cmd *cmd)
{
	t_red	*tmp;

	tmp = *tab_red;
	cmd_tab[index->i + 1] = handle_cmd_file_word_deux(cmd_tab[index->i][index->j], cmd, cmd_tab[index->i + 1], tab_red);
	if (!cmd_tab[index->i + 1])
		return (free_split(cmd_tab), free_end_tab(cmd_tab, index->i + 1), NULL);				
	if (ft_strlen(cmd_tab[index->i + 1]) == 0)
	{
		cmd_tab = realloc_cmd(cmd_tab, index->i + 1);
		if (!cmd_tab)
			return (NULL);
		index->tab_len = command_counter(cmd_tab);
	}
	cmd_tab[index->i] =  realloc_word_red_at_end(cmd_tab[index->i], tmp);
	if (!cmd_tab[index->i])
		return (free_split(cmd_tab), free_end_tab(cmd_tab, index->i), NULL);
	return (cmd_tab);
}

char	**extract_file(t_cmd *cmd, char **cmd_tab, t_red **tab_red, t_index *index)
{
	if ((ft_strlen(cmd_tab[index->i]) == 1 && (*tab_red)->type == simple) 
		|| (ft_strlen(cmd_tab[index->i]) == 2 && (*tab_red)->type == double_))
	{
		cmd_tab = simple_token(cmd_tab, index, tab_red, cmd);
		if (!cmd_tab)
			return (NULL);
	}
	else if ((cmd_tab[index->i][index->j + 1] != '\0' && (*tab_red)->type == simple) 
		|| (cmd_tab[index->i][index->j + 1] != '\0' 
			&& (cmd_tab[index->i][index->j + 2] != '\0' && (*tab_red)->type == double_)))
	{
		cmd_tab = two_token_in_one_word(cmd_tab, index, tab_red, cmd);
		if (!cmd_tab)
			return (NULL);
	}
	else
	{
		cmd_tab = three_token_in_two_word(cmd_tab, index, tab_red, cmd);
		if (!cmd_tab)
			return (NULL);
	}
	index->j = 0;
	//*tab_red = (*tab_red)->next;
    return (cmd_tab);
}
