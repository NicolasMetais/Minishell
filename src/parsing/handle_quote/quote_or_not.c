/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_or_not.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-02 12:44:10 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-02 12:44:10 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	no_quote(t_quote *ctx, t_free_var *f)
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
	ctx->str -= ctx->i;
	ctx->str = realloc_line(ctx->str, ctx->i, NULL);
	if (!ctx->str)
	{
		realloc_line_failed(ctx, f);
		return ;
	}
	ctx->no_quote = false;
}

void	get_word_in_quote(t_quote *ctx, t_free_var *f)
{
	if (ctx->i > 1)
	{
		f->tmp = ft_strndup(ctx->str, ctx->i - 1);
		if (!f->tmp)
		{
			ndup_failed(ctx, f);
			return ;
		}
	}
	else
	{
		f->tmp = ft_strndup(ctx->str, ctx->i);
		if (!f->tmp)
		{
			ndup_failed(ctx, f);
			return ;
		}
	}
	ctx->word = ft_strjoin_custom(ctx->word, f->tmp);
	if (!ctx->word)
	{
		join_custom_failed(ctx, f);
		return ;
	}
	free(f->tmp);
}

void	realloc_line_in_quote(t_quote *ctx, t_free_var *f)
{
	if (ctx->i == 1)
	{
		ctx->str = realloc_line(ctx->str, ctx->i, NULL);
		if (!ctx->str)
		{
			realloc_line_failed(ctx, f);
			return ;
		}
	}
	else
	{
		ctx->str = realloc_line(ctx->str, ctx->i + 1, NULL);
		if (!ctx->str)
		{
			realloc_line_failed(ctx, f);
			return ;
		}
		ctx->k--;
	}
}

void	quote_or_not(t_quote *ctx)
{
	t_free_var	f;

	free_var_init(ctx, &f);
	if (ctx->no_quote == true)
	{
		no_quote(ctx, &f);
		if (ctx->word == NULL)
			return ;
	}
	else
	{
		get_word_in_quote(ctx, &f);
		if (ctx->word == NULL)
			return ;
		ctx->str -= ctx->i;
		realloc_line_in_quote(ctx, &f);
		if (ctx->word == NULL)
			return ;	
		if (*ctx->str == '\'' || *ctx->str == '"')
			ctx->c = *ctx->str;
		else	
			ctx->c = 0;
	}
	quote_or_not_free(ctx, &f);
}