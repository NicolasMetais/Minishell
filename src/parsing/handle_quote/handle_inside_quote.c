/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inside_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 20:20:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-03 20:20:07 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_word_realloc(t_quote *ctx, t_free_var *f)
{
	ctx->str -= ctx->i;
	ctx->str = realloc_line(ctx->str, ctx->i + 1, NULL);
	if (!ctx->str)
	{
		realloc_line_failed(ctx, f);
		return ;
	}
	ctx->k--;
	if (*ctx->str == '\'' || *ctx->str == '"')
		ctx->c = *ctx->str;
	else
		ctx->c = 0;
}

void	simple_word(t_quote *ctx, t_free_var *f)
{
	f->tmp = ft_strndup(ctx->str, ctx->i);
	if (!f->tmp)
	{
		ndup_failed(ctx, f);
		return ;
	}
	ctx->word = ft_strjoin_custom(ctx->word, f->tmp);
	if (!ctx->word)
	{
		join_custom_failed(ctx, f);
		return ;
	}
	free(f->tmp);
	simple_word_realloc(ctx, f);
	if (ctx->word == NULL)
		return ;
	quote_or_not_free_2(ctx, f);
}

void	handle_inside_quote(t_quote *ctx)
{
	t_free_var	f;

	free_var_init(ctx, &f);
	if (*ctx->str != '\'' && *ctx->str != '"')
		simple_word(ctx, &f);
	else
		quote_or_not(ctx);
}
