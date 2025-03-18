/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:52:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 01:55:53 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_cmd *head, t_cmd *new)
{
	t_cmd	*tmp;

	if (head == NULL)
	{
		head = new;
		tmp = NULL;
		return ;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp = NULL;
	return ;
}

int	command_counter(char **line_split)
{
	int	i;

	if (!line_split)
		return (0);
	i = 0;
	while (line_split[i])
		i++;
	return (i);
}

t_boolean	is_redirection(char	*s)
{
	if (ft_strncmp(s, "<", 1) == 0)
		return (true);
	if (ft_strncmp(s, "<<", 1) == 0)
		return (true);
	if (ft_strncmp(s, ">", 1) == 0)
		return (true);
	if (ft_strncmp(s, ">>", 1) == 0)
		return (true);
	return (false);
}

t_boolean	is_redirection_char(char s)
{
	if (s == '<')
		return (true);
	if (s == '>')
		return (true);
	return (false);
}

t_boolean	is_a_directory(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!arg)
		return (false);
	while (*arg)
	{
		if (*arg != '/' && *arg != '.')
			return (false);
		if (*arg == '.')
			i++;
		if (i > 2)
			return (false);
		if (*arg == '/')
		{
			i = 0;
			j = 1;
		}
		arg++;
	}
	if (j == 0)
		return (false);
	return (true);
}
