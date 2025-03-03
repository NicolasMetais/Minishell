/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quet_quote_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-20 19:08:38 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-20 19:08:38 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_custom(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;

	i = 0;
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buffer)
		return (free((char *)s1), NULL);
	while (*s1)
	{
		buffer[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{	
		buffer[i] = *s2;
		s2++;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_pignouf(char *line)
{
	t_pignouf	var;

	var.i = 0;
	var.j = 0;
	var.len = ft_strlen(line) - 1;
	while (line[var.i] == ' ')
		var.i++;
	while (line[var.len] == ' ')
	{
		var.len--;
		var.j++;
	}
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

t_boolean	is_empty(char *str)
{
	char	*tmp;

	tmp = str;
	tmp -= 1;
	if (*str == '"' || *str == '\'')
	{
		if (*tmp == *str)
			return (true);
	}
	return (false);
}

void	free_var_init(t_quote *ctx, t_free_var *f)
{
	f->str = ctx->str - ctx->i;
	fprintf(stderr, "fstr : %p, '%s'\n", f->str, f->str);
	f->word = ctx->word;
	f->tmp = NULL;
}

void get_word_increment(t_quote	*ctx)
{
	ctx->k--;
	if (ctx->k >= 0)
	{
		ctx->str++;
		ctx->i++;
	}
}

