/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-15 14:57:16 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-15 14:57:16 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_inword(char *line, int i, char c)
{
	char	*new;
	size_t	j;

	line -= i;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(line) - 2);
	if (!new)
		return (NULL);
	while (*line)
	{
		if (*line == c && j < ft_strlen(line) - 2)
			line++;
		new[j] = *line;
		j++;
		line++;
	}
	free(line);
	new[j] = '\0';
	return (new);
}

char	*is_next(char *line, char c, int i)
{
	int		k;
	char	*new;

	line -= i;
	i = 0; 
	k = 0;
	while (*line)
	{
		if (*line == c)
			k++;
		if (*line == ' ' && k == 2)
		{
			new = ft_strndup(line, i);
			if (!new)
				return (NULL);
			return (new);
		}
		line++;
		i++;
	}
	return (NULL);
}

char	*handle_no_quote(char *line)
{
	int		i;
	char	c;
	char	*new;

	i = 0;
	line++;
	c = 0;
	while (*line && *line != ' ')
	{
		line++;
		i++;
		if (*line == '\'' || *line == '"')
		{	
			c = *line;
			new = is_next(line, c, i);
			if (new)
				return (new);
		}			
	}
	new = ft_strndup(line, i + 1);
	if (!new)
		return (NULL);
	return (new);
}

int	is_next_remove(char *line, char c, int i)
{
	int		k;

	line -= i;
	i = 0; 
	k = 0;
	while (*line)
	{
		if (*line == c)
			k++;
		if (*line == ' ' && k == 2)
			return (i);
		line++;
		i++;
	}
	return (0);
}


char	*remove_no_quote(char *line, int *end)
{
	int		i;
	char	c;
	char	*new;
	int		k;

	i = 1;
	line++;
	c = 0;
	while (*line && *line != ' ')
	{
		line++;
		i++;
		if ((c == '\'' && *line == '\'')  || (c == '"' && *line == '"'))
		{
			k = is_next_remove(line, c, i);
			if (k)
			{
				line -= i;
				new = realloc_line(line, k, end);
				if (!new)
					return (NULL);
			}
		}
		if (*line == '\'' || *line == '"')
			c = *line;			
	}
	line -= i;
	new = realloc_line(line, i, end);
	if (!new)
		return (NULL);
	return (new);
}