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

t_boolean	pipe_valid(char *line)
{
	char	*tmp;

	tmp = line;
	if (*line != '\0')
		line++;
	while (*line && *line == ' ')
		line++;
	if (*line == '|')
		return (false);
	return (true);
}

void	increment(t_pipe_var *ctx)
{
	ctx->str++;
	ctx->c++;
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

char	*ft_strnjoin(char const *s1, char const *s2, int c)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	if (!s1)
		return (ft_strndup((char *)s2, c));
	s2 -= c;
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + c + 1));
	if (!buffer)
		return (NULL);
	while (*s1 && s1)
	{
		buffer[i] = *s1;
		s1++;
		i++;
	}
	j = 0;
	while (j < c)
	{
		buffer[i + j] = *s2;
		s2++;
		j++;
	}
	buffer[i + j] = '\0';
	return (buffer);
}
