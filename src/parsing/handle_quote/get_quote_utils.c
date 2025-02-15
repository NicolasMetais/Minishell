/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 17:09:02 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-12 17:09:02 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_sep(char	c)
{
	if (c == ' ')
		return (0);
	if (c == '"')
		return (2);
	if (c == '\'')
		return (1);
	return (-1);
}

char	*ft_strndup(char *line, int c)
{
	char	*dup;
	int		i;

    i = 0;
	line -= c;
	dup = malloc(sizeof(char) * (c + 1));
	if (!dup)
		return (NULL);
	while (i < c)
	{
		dup[i] = *line;
		line++;
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strndup_bis(char *line, int c)
{
	char	*dup;
	int		i;

    i = 0;
	dup = malloc(sizeof(char) * (c + 1));
	if (!dup)
		return (NULL);
	while (i < c)
	{
		dup[i] = line[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
