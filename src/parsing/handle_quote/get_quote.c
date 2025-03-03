/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 07:50:50 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-16 07:50:50 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*extract_word(t_quote *ctx)
{
	char	*tmp;
	
	ctx->tmp = ctx->str - ctx->i;
	if (ctx->quote == false && ctx->i == 1 && is_empty(ctx->str))
	{
		ctx->str = realloc_line(ctx->str, ctx->i, NULL);
		if (!ctx->str)
			return (free(ctx->tmp), free(ctx->word), NULL);
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
	if (ctx->quote == true)
	{			
		fprintf(stderr, "JE SUIS UTILE");
		tmp = ft_strndup(ctx->str, ctx->i - 1);
		if (!tmp)
			return (free(ctx->str), free(ctx->word), NULL);
		ctx->word = ft_strjoin_custom(ctx->word, tmp);
		free(tmp);
		if (!ctx->word)
			return (free(ctx->str), NULL);
		ctx->str = realloc_line(ctx->str, ctx->i, NULL);
		if (!ctx->str)
			return (free(ctx->tmp), free(ctx->word), NULL);
		ctx->tmp = ctx->str;
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
	while (ctx.k != -1 )
	{
		if (ctx.c == 0 && (*ctx.str == '"' || *ctx.str == '\''))
			get_word_turn_true(&ctx);
		if ((ctx.c == *ctx.str || ctx.no_quote == true || ctx.k == 0) && ctx.i != 0)
		{
			if (ctx.c == *ctx.str)
				ctx.quote = false;
			ctx.word = extract_word(&ctx);
			if (ctx.word == NULL)
				return (NULL);
			if (ctx.k <= 0)
				break;
			ctx.i = 0;
		}
		else
			get_word_increment(&ctx);
	}
	return (ctx.word);
}

void	handle_quote(t_pipe_var *ctx)
{
	char	**tmp;

	tmp = ctx->cmd_tab;
	ctx->tmp = get_word(ctx->str, ctx->c);
	if (!ctx->tmp)
	{
		get_word_failed(ctx);
		return ;
	}
	ctx->str -= ctx->c;
	ctx->fstr = ctx->str;
	ctx->str = realloc_line(ctx->str, ctx->c + 1, &ctx->end);
	if (!ctx->str)
	{
		realloc_line_handle_quote_failed(ctx);
		return ;
	}
	ctx->cmd_tab = realloc_add_to_tab(ctx->cmd_tab, ctx->tmp);
	if (!ctx->cmd_tab)
	{
		cmd_tab_handle_quote_failed(tmp, ctx);
		return ;
	}
	reset_handle_quote(ctx);
}

void	get_quote_turn_true(t_pipe_var *ctx)
{
	ctx->i = *ctx->str;
	ctx->quote = true;
	increment(ctx);
}

char	**get_quote_dup(char *line)
{
	t_pipe_var	ctx;

	quote_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	while (ctx.end == 0)
	{	
		if (ctx.i == 0 && (*ctx.str == '"' || *ctx.str == '\''))
			get_quote_turn_true(&ctx);
		if (ctx.i == *ctx.str)
		{
			ctx.quote = false;
			ctx.i = 0;
		}
		if ((*ctx.str == ' ' && ctx.quote == false) || ft_strlen(ctx.str) == 0)
		{	
			handle_quote(&ctx);
			if (!ctx.cmd_tab)
				return (NULL);
		}
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
