/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 12:36:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-12 12:36:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_quote(char *line)
{
	char	**tab;
	char	*tmp;
	int		c;

	tab = NULL;
	while (line)
	{	
		c = 0;
		fprintf(stderr, "%s\n", line);
		while (line && is_a_sep(*line) == -1)
		{
			line++;
			c++;	
		}
		if (is_a_sep(*line) == 0)
		{
			tmp = ft_strndup(line, c);
			tab = realloc_quote(tab, tmp);
		}
		if (is_a_sep(*line) == 1)
		{
			line++;
			tmp = handle_double_quote(line);
			tab = realloc_quote(tab, tmp);
		}
		if (is_a_sep(*line) == 2)
		{
			line++;
			tmp = handle_simple_quote(line);
			tab = realloc_quote(tab, line);
		}
	}
	return (tab);
}