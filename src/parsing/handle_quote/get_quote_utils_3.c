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

char	*get_begin(char *str, int c)
{
	int		i;

	i = 0;
	while ((*str != '"' && *str != '\'') && i < c)
	{
		i++;
		str++;
	}
	if (i == 0)
		return (NULL);
	else
		return (ft_strndup(str, i));
}

char	*get_end(char *str, int c)
{
	int		i;
	char	*end;

	i = 0;
	if (c > (int)ft_strlen(str))
		return (NULL);
	str += c;
	while ((*str != '"' && *str != '\'') && i < c)
	{
		str--;
		i++;
	}
	if (*str != '"' && *str != '\'')
		return (NULL);
	end = ft_strdup_end(str, i);
	if (!end)
		return (NULL);
	return (end);
}

void	t_in_quote_init(t_in_quote *ctx, char *str, int c)
{
	char	*tmp;

	ctx->i = 0;
	ctx->type = 0;
	ctx->str = ft_strdup(str);
	if (!ctx->str)
		return ;
	tmp = ctx->str;
	if (quote_inside(ctx->str, c))
	{
		ctx->begin = get_begin(ctx->str, c);
		if (ctx->begin)
			ctx->str = remove_begin(ctx->str, to_remove_begin(ctx->str));
		ctx->end = get_end(tmp, c);
		if (ctx->end)
			ctx->str = remove_end(ctx->str, to_remove_end(ctx->str, space_in_quote(ctx->str)));
	}
	else
	{
		ctx->begin = NULL;
		ctx->end = NULL;
	}
	ctx->mid = NULL;
}

char	*join_word(t_in_quote *ctx)
{
	ctx->new = ft_strjoin_custom(ctx->begin, ctx->mid);
	if (!ctx->new)
		return (NULL);
	ctx->new = ft_strjoin_custom(ctx->new, ctx->end);
	if (!ctx->new)
		return (NULL);
	return (ctx->new);
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
