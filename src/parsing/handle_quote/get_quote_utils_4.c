/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 18:16:20 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-21 18:16:20 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_in_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i])
		i++;
	i--;
	if (c == '\'' || c == '"')
	{
		if (str[i] == c)
			return (true);
	}
	return (false);
}

t_boolean	quote_inside(char *str, int i)
{
	char	c;
	int		j;

	j = 0;
	c = 0;
	while (*str && j < i)
	{	
		if (*str == c)
			return (true);
		if ((*str == '\'' || *str == '"') && c == 0)
			c = *str;
		str++;
		j++;
	}
	return (false);
}

t_boolean	space_in_quote(char *str)
{
	char		c;
	t_boolean	status;
	int			i;

	status = false;
	i = 0;
	c = 0;
	while (*str)
	{
		if (*str == c)
			status = false;
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			status = true;
		}
		if (*str == ' ' && status == false)
			return (i);
		str++;
		i++;
	}
	return (i);
}
