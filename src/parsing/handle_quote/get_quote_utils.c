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

t_boolean	is_in_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i])
		i++;
	i--;
	fprintf(stderr, "str : '%s'\n", str);
	if (c == '\'' || c == '"')
	{
		if (str[i] == c)
		{
			fprintf(stderr, "true\n");
			return (true);
		}
	}
	fprintf(stderr, "false\n");
	return (false);
}