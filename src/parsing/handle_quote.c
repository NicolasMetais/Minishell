/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 17:03:10 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-12 17:03:10 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_backward(char	*line)
{
	int	i;
	int	j;
	
	j = 0;
	i = 0;
	while (line - 1 && j < 2)
	{
		line--;
		j++;
	}
	if (line && is_a_sep(*line) != -1)
	{
		line += 2;
		return (0);
	}
	while (line - 1 && is_a_sep(*line) == -1)
	{
		line--;
		i++;
	}
	line += i + 2;
	return (i + 2);

	return (0);
}

char	*nothing_backward_double(char *line)
{
	char	*tmp;
	int 	c;

	c = 0;
	while (*line != '\"' && line)
	{
		c++;
		line++;
	}
	if (*line == '\0')
	{
		line--;
		while (*line != '"')
			line--;
		tmp = ft_strndup("\"", 1);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	tmp = ft_strndup(line, c);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*nothing_backward_simple(char *line)
{
	char	*tmp;
	int 	c;

	c = 0;
	while (*line != '\'' && line)
	{
		c++;
		line++;
	}
	if (*line == '\0')
	{
		line--;
		while (*line != '\'')
			line--;
		tmp = ft_strndup("'", 1);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	tmp = ft_strndup(line, c);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*handle_double_quote(char *line)
{
	int		k;
	int		c;
	char	*tmp;

	c = 0;
	k = check_backward(line);
	if (k == 2)
		return (nothing_backward_double(line));
	else
	{
		while (line && *line != '"')
		{
			line++;
			c++;
		}
		tmp = ft_strndup(line, k + c);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

char	*handle_simple_quote(char *line)
{
	int		k;
	int		c;
	char	*tmp;

	c = 0;
	k = check_backward(line);
	if (k == 2)
		return (nothing_backward_simple(line));
	else
	{
		while (line && *line != '\'')
		{
			line++;
			c++;
		}
		tmp = ft_strndup(line, k + c);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}