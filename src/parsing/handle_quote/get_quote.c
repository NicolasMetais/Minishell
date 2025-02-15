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

char	*pignouf(char *str)
{
	char	*line;
	size_t		len;

	len = ft_strlen(str);
	while (str[len - 1] == ' ')
		len--;
	if (len != ft_strlen(str))
		line = ft_strndup_bis(str, len - 1);
	else
		return (str);
	if (!line)
		return (NULL);
	return (line);
}

void	handle_when_is_a_sep(t_quote *ctx)
{
	ctx->tmp = handle_quote(ctx->str);
	ctx->str = handle_remove(ctx->str, &ctx->end);
	ctx->tab = realloc_quote(ctx->tab, ctx->tmp);
}

void	handle_when_is_not_quote(t_quote *ctx)
{
	ctx->tmp = handle_no_quote(ctx->str);
	ctx->str = handle_remove(ctx->str, &ctx->end);
	ctx->tab = realloc_quote(ctx->tab, ctx->tmp);
}

void	ctx_init(t_quote *ctx, char *line)
{
	ctx->tab = NULL;
	ctx->end = 0;
	ctx->str = pignouf(line);
}

char	**get_quote(char *line)
{
	t_quote	ctx;

	ctx_init(&ctx, line);
	while (ctx.end == 0 && *ctx.str)
	{
		while (*ctx.str == ' ')
			ctx.str++;
		if (is_a_sep(*ctx.str) == 1 || is_a_sep(*ctx.str) == 2)
			handle_when_is_a_sep(&ctx);
		else
			handle_when_is_not_quote(&ctx);
	}
	return (ctx.tab);
}