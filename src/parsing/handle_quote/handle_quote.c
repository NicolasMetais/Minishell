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

char	*handle_simple_quote(char *line)
{
	int		c;
	char	*word;

	c = 0;
	line++;
	while (*line && *line != '\'')
	{
		line++;
		c++;
	}
	word = ft_strndup(line, c);
	if (!word)
		return (NULL);
	return (word);
}

char	*remove_single_quote(char *line, int *end)
{
	int		c;
	char	*new;

	c = 1;
	line++;
	while (*line && *line != '\'')
	{
		line++;
		c++;
	}
	line -= c;
	c++;
	new = realloc_line(line, c, end);
	if (!new)
		return (NULL);
	return (new);
}

char	*remove_double_quote(char *line, int *end)
{
	int		c;
	char	*new;

	c = 1;
	line++;
	while (*line && *line != '"')
	{
		line++;
		c++;
	}
	line -= c;
	c++;
	new = realloc_line(line, c, end);
	if (!new)
		return (NULL);
	return (new);
}


char	*handle_remove(char *line, int *end)
{
	char	*new;

	if (is_a_sep(*line) == 1)
	{
		new = remove_single_quote(line, end);
		return (new);
	}
	else if (is_a_sep(*line) == 2)
	{
		new = remove_double_quote(line, end);
		return (new);
	}
	else
	{
		new = remove_no_quote(line, end);
		return (new);
	}
}

char	*handle_double_quote(char *line)
{
	int		c;
	char	*word;

	c = 0;
	line++;
	while (*line && *line != '"')
	{
		line++;
		c++;
	}
	word = ft_strndup(line, c);
	if (!word)
		return (NULL);
	return (word);
}

char	*handle_quote(char *line)
{
	char	*word;

	if (is_a_sep(*line) == 1)
	{
		word = handle_simple_quote(line);
		return (word);
	}
	else
	{
		word = handle_double_quote(line);
		return (word);
	}
	return ("zbi");
}