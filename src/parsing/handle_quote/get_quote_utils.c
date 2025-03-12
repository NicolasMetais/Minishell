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

char	*ft_pignouf_prime(char *line)
{
	t_pignouf	var;

	var.i = 0;
	var.j = 0;
	var.len = ft_strlen(line) - 1;
	while (line[var.i] == ' ')
		var.i++;
	while (line[var.len] == ' ' && var.len != 0)
	{
		var.len--;
		var.j++;
	}
	if (var.len == 0)
		return (NULL);
	var.new = malloc(sizeof(char) * (ft_strlen(line) - (var.i + var.j)) + 1);
	if (!var.new)
		return (NULL);
	var.j = 0;
	while (var.i <= var.len)
	{
		var.new[var.j] = line[var.i];
		var.i++;
		var.j++;
	}
	var.new[var.j] = '\0';
	return (var.new);
}
