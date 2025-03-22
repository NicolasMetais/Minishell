/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 07:50:50 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 01:57:42 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_quote_dup_2(t_pipe_var *ctx)
{
	char	*tmp;

	handle_quote(ctx);
	if (!ctx->cmd_tab)
		return (NULL);
	tmp = ctx->str;
	if (ctx->end == 0 && *ctx->str == ' ')
	{
		ctx->str = ft_pignouf_prime(ctx->str);
		if (!ctx->str)
			return (free_split(ctx->cmd_tab), free(tmp), NULL);
		free(tmp);
	}
	return (ctx->str);
}

void	ninho(t_pipe_var *ctx)
{
	ctx->quote = false;
	ctx->i = 0;
}

char	**get_quote_dup(char *line)
{
	t_pipe_var	ctx;

	quote_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	if (ft_strlen(ctx.str) == 1)
		return (realloc_add_to_tab(ctx.cmd_tab, ctx.str));
	while (ctx.end == 0)
	{	
		if (ctx.i == 0 && (*ctx.str == '"' || *ctx.str == '\''))
			get_quote_turn_true(&ctx);
		if (ctx.i == *ctx.str)
			ninho(&ctx);
		if ((*ctx.str == ' ' && ctx.quote == false) || ft_strlen(ctx.str) == 0)
		{	
			ctx.str = get_quote_dup_2(&ctx);
			if (!ctx.str)
				return (NULL);
		}
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
