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

char	*get_one_line_of_cmd_split(char **cmd_split)
{
	char	*tmp;
	char	*cmd_one_line;
	int		i;

	i = 0;
	cmd_one_line = NULL;
	while(cmd_split[i])
	{
		tmp = cmd_one_line;
		cmd_one_line = ft_strjoin_custom(cmd_one_line, cmd_split[i]);
		//if (!cmd_one_line)
			
		if (tmp)
			free(tmp);
		i++;
	}
	return (cmd_one_line);
}

t_file	*add_to_file_list(t_file *lst, t_file *new)
{
	t_file *tmp;

	if (!lst)
	{
		tmp = NULL;
		return (new);
	}
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

t_file	*create_file(char *file, t_file *list, t_type_red type, int complete)
{
	t_file	*new;
	t_file	*tmp;

	if (!list)
	{	
		new = malloc(sizeof(t_file));
		if (!new)
			return (NULL);
		new->type = type;
		if (complete == 1)
			new->complete = true;
		else
			new->complete = false;
		new->file = file;
		new->next = NULL;
		list = add_to_file_list(list, new);
		return (list);
	}
	else if (list->complete == true)
	{
		new = malloc(sizeof(t_file));
		if (!new)
			return (NULL);
		new->type = type;
		if (complete == 1)
			new->complete = true;
		else
			new->complete = false;
		new->file = file;
		new->next = NULL;
		list = add_to_file_list(list, new);
		return (list);
	}
	else if (list->complete == false)
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		list->file = file;
		list->complete = true;
		return (list);
	}
	return (list);
}

void	add_file_to_cmd(char *file, char c, t_cmd *cmd, t_red *tab_red, int complete)
{
	if (c == '<')
		cmd->in = create_file(file, cmd->in, tab_red->type, complete);
	else
		cmd->out = create_file(file, cmd->out, tab_red->type, complete);
}

char	*handle_cmd_file_word_un(t_cmd *cmd, char *str, t_red *tab_red)
{
	char	*file;
	char	*tmp;
	char	c;
	int		i;
	int		j;

	i = 0;
	tmp = str;
	j = 0;
	while (*str && !is_redirection_char(*str))
	{
		str++;
		j++;
	}
	c = *str;
	if (tab_red->type == double_)
		str++;
	str++;
	while (*str && !(is_redirection_char(*str) && tab_red->valid == true))
	{	
		str++;
		i++;
		if (is_redirection_char(*str)  && tab_red->valid == false)
			tab_red = tab_red->next;
	}
	file = ft_strndup(str, i);
	add_file_to_cmd(file, c, cmd, tab_red, 1);
	if (tab_red->type == double_)
		i++;
	str = realloc_str_file(tmp, i, j);
	return (free(tmp), str);
}

char	*handle_cmd_file_word_deux(char c, t_cmd *cmd, char *str, t_red *tab_red)
{
	char	*file;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	while (*str && !(is_redirection_char(*str) && tab_red->valid == true))
	{	
		str++;
		i++;
		if (is_redirection_char(*str))
			tab_red = tab_red->next;
	}
	file = ft_strndup(str, i);
	add_file_to_cmd(file, c, cmd, tab_red, 1);
	str = realloc_line(tmp, i, NULL);
	return (free(tmp), str);

}

char	*realloc_word_red_at_end(char *str, t_red *red_tab)
{
	char	*new;
	int		i;

	i = 0;
	if (red_tab->type == simple)
	{
		new = malloc(sizeof(char) * ft_strlen(str));
		if (!new)
			return(NULL);
	}
	else
	{
		new = malloc(sizeof(char) * ft_strlen(str) - 1);
		if (!new)
			return (NULL);
	}
	while (!is_redirection_char(*str))
	{
		new[i] = *str;
		i++;
		str++;
	}
	new[i] = '\0';
	return (new);
}

char	**get_file(t_cmd *cmd, char **cmd_tab, t_red *tab_red)
{
	int	j;
	int	i;
	int	tab_len;

	j = 0;
	i = 0;
	tab_len = command_counter(cmd_tab);
	while (cmd_tab[i] && cmd_tab[i][j])
	{
		if (is_redirection_char(cmd_tab[i][j]) && tab_red->valid == false)
			tab_red = tab_red->next;
		if (is_redirection_char(cmd_tab[i][j]) && tab_red->valid == true)
		{
			if ((ft_strlen(cmd_tab[i]) == 1 && tab_red->type == simple) || (ft_strlen(cmd_tab[i]) == 2 && tab_red->type == double_))
			{
				cmd_tab[i + 1] = handle_cmd_file_word_deux(cmd_tab[i][j], cmd, cmd_tab[i + 1], tab_red);
				if (ft_strlen(cmd_tab[i + 1]) == 0)
				{
					cmd_tab = realloc_cmd(cmd_tab, i + 1);
					tab_len = command_counter(cmd_tab);
				}
				cmd_tab = realloc_cmd(cmd_tab, i);
				tab_len = command_counter(cmd_tab);
			}
			else if ((cmd_tab[i][j + 1] != '\0' && tab_red->type == simple) || (cmd_tab[i][j + 1] != '\0' && (cmd_tab[i][j + 2] != '\0' && tab_red->type == double_)))
			{
				cmd_tab[i] = handle_cmd_file_word_un(cmd, cmd_tab[i], tab_red);
				if (ft_strlen(cmd_tab[i]) == 0)
				{
					cmd_tab = realloc_cmd(cmd_tab, i);
					tab_len = command_counter(cmd_tab);
				}
			}
			else
			{
				cmd_tab[i + 1] = handle_cmd_file_word_deux(cmd_tab[i][j], cmd, cmd_tab[i + 1], tab_red);
				if (ft_strlen(cmd_tab[i + 1]) == 0)
				{
					cmd_tab = realloc_cmd(cmd_tab, i + 1);
					tab_len = command_counter(cmd_tab);
				}
				cmd_tab[i] =  realloc_word_red_at_end(cmd_tab[i], tab_red);
			}
			j = 0;
			tab_red = tab_red->next;
		}
		else
			j++;
		if (j == (int)ft_strlen(cmd_tab[i]))
		{
			if (i < tab_len)
				i++;
			j = 0;	
		}
	}
	return (cmd_tab);
}

char	**get_fd(t_cmd *cmd, char **cmd_split, t_red *tab_red)
{
	char	*cmd_one_line;
	t_red	*tmp;

	tmp = tab_red;
	cmd_one_line = get_one_line_of_cmd_split(cmd_split);
	if (!cmd_one_line)
		return (NULL);
	if (unexpected_token_red(cmd_one_line, tab_red))
		return (free(cmd_one_line), free_split(cmd_split), NULL);
	free(cmd_one_line);
	cmd_split = get_file(cmd, cmd_split, tmp);
	return (cmd_split);
}