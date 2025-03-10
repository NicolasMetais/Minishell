/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-08 12:09:30 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-08 12:09:30 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_one_line_of_cmd_split(char **cmd_split)
{
	char	*tmp;
	char	*cmd_one_line;
	int		i;

	i = 0;
	cmd_one_line = NULL;
	tmp = NULL;
	while (cmd_split[i])
	{
		cmd_one_line = ft_strjoin_custom(cmd_one_line, cmd_split[i]);
		if (!cmd_one_line)
			return (free(tmp), NULL);
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		tmp = cmd_one_line;
		i++;
	}
	return (cmd_one_line);
}

char	*realloc_word_red_at_end(char *str, t_red *red_tab)
{
	char	*new;
	char	*tmp;
	int		i;

	i = -1;
	tmp = str;
	if (red_tab->type == simple)
	{
		new = malloc(sizeof(char) * ft_strlen(str));
		if (!new)
			return (free(str), NULL);
	}
	else
	{
		new = malloc(sizeof(char) * ft_strlen(str) - 1);
		if (!new)
			return (free(str), NULL);
	}
	while (!is_redirection_char(*str))
	{
		new[++i] = *str;
		str++;
	}
	new[i] = '\0';
	return (free(tmp), new);
}

t_boolean	get_file_incr_false(t_index *index, char **tab, t_red **tab_red)
{
	if ((*tab_red)->type == double_)
		index->j++;
	index->j++;
	*tab_red = (*tab_red)->next;
	if (index->j == (int)ft_strlen(tab[index->i]))
	{
		if (index->i < index->tab_len)
			index->i++;
		if (index->i >= index->tab_len)
			return (true);
		index->j = 0;
	}
	return (false);
}

void	get_file_increment(t_index *index, char **cmd_tab, t_red **tab_red)
{
	(void)tab_red;
	if (index->j == (int)ft_strlen(cmd_tab[index->i]))
	{
		if (index->i < index->tab_len)
			index->i++;
		index->j = 0;
	}
}

void	get_file_index_init(t_index *index, char **cmd_tab)
{
	index->j = 0;
	index->i = 0;
	index->tab_len = command_counter(cmd_tab);
}
