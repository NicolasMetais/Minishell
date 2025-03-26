/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:09:02 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/26 10:06:54 by nmetais          ###   ########.fr       */
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

void	pignouf_init(t_pignouf *var, char *line)
{
	var->i = 0;
	var->j = 0;
	var->len = ft_strlen(line) - 1;
}

char	*ft_pignouf_prime(char *line)
{
	t_pignouf	var;

	pignouf_init(&var, line);
	while ((line[var.i] >= 9 && line[var.i] <= 13)
		|| line[var.i] == 127 || line[var.i] == 32)
		var.i++;
	while (((line[var.len] >= 9 && line[var.len] <= 13)
			|| line[var.len] == 127 || line[var.len] == 32) && var.len != 0)
		pignouf_prime_incr(&var.j, &var.len);
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
