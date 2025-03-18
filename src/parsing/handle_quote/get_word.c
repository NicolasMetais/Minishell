/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:24:22 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 02:00:32 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_word(t_quote *ctx)
{
	ctx->tmp = ctx->str - ctx->i;
	if (ctx->quote == false && ctx->i == 1 && is_empty(ctx->str))
	{
		ctx->str = realloc_line(ctx->str, ctx->i, NULL);
		if (!ctx->str)
			return (free(ctx->tmp), free(ctx->word), NULL);
		ctx->k--;
		if (ft_strlen(ctx->str) == 1 && (*ctx->str == '\''
				|| *ctx->str == '"'))
			ctx->k--;
		if (ctx->k == 0)
			free(ctx->str);
		ctx->c = 0;
		if (!ctx->word)
			return (free(ctx->tmp), ft_strdup(""));
		return (free(ctx->tmp), ctx->word);
	}
	if (ctx->quote == false)
	{
		handle_inside_quote(ctx);
		return (ctx->word);
	}
	return (ctx->word);
}

void	get_word_turn_true(t_quote *ctx)
{
	ctx->quote = true;
	ctx->c = *ctx->str;
	if (ctx->i == 0)
		get_word_increment(ctx);
	if (ctx->i > 1)
		ctx->no_quote = true;
}

char	*get_word(char *str, int j)
{
	t_quote	ctx;

	get_word_init(&ctx, str, j);
	if (!ctx.str)
		return (NULL);
	while (ctx.k != -1)
	{
		if (ctx.c == 0 && (*ctx.str == '"' || *ctx.str == '\''))
			get_word_turn_true(&ctx);
		if ((ctx.c == *ctx.str || ctx.no_quote == true || ctx.k == 0)
			&& ctx.i != 0)
		{
			if (ctx.c == *ctx.str)
				ctx.quote = false;
			ctx.word = extract_word(&ctx);
			if (ctx.word == NULL)
				return (NULL);
			if (ctx.k <= 0)
				break ;
			ctx.i = 0;
		}
		else
			get_word_increment(&ctx);
	}
	return (ctx.word);
}
