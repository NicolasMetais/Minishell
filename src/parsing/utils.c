/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 12:52:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-07 12:52:44 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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