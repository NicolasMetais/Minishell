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

void	quote_var_init(t_pipe_var *ctx, char *line)
{
	ctx->c = 0;
	ctx->i = 0;
	ctx->end = 0;
	ctx->cmd_tab = NULL;
	ctx->valid = false;
	ctx->quote = false;
	ctx->str = ft_pignouf(line);
	ctx->fstr = ctx->str;
}

char	*inside_quote(char *str, int c)
{
	t_in_quote	ctx;
	char		*new;

	str -= c;
	t_in_quote_init(&ctx, str, c);
	while (ctx.i < c && ft_strlen(ctx.str) != 0)
	{
		if (*ctx.str == ctx.type)
		{
			ctx.mid = handle_inside_quote(&ctx);
			if (ft_strlen(ctx.str) == 0 || *ctx.str == ' ')
				break ;
			ctx.str++;
		}
		if ((*ctx.str == '"' || *ctx.str == '\'') && ctx.type == 0)
			ctx.type = *ctx.str;
		else
			ctx.i++;
		ctx.str++;
	}
	new = join_word(&ctx);
	if (!new)
		return (ft_strndup(ctx.str, c));
	return (new);
}

void	handle_quote_dup(t_pipe_var *ctx)
{
	if (ctx->quote == false || ft_strlen(ctx->str + 1) == 0)
	{
		if (ft_strlen(ctx->str + 1) == 0)
		{
			ctx->str++;
			ctx->tmp = inside_quote(ctx->str, ctx->c + 1);
		}
		else
			ctx->tmp = inside_quote(ctx->str, ctx->c);
		ctx->cmd_tab = realloc_add_to_tab(ctx->cmd_tab, ctx->tmp);
		ctx->str -= ctx->c;
		ctx->str = realloc_line(ctx->str, ctx->c + 1, &ctx->end);
		free(ctx->fstr);
		ctx->fstr = ctx->str;
		ctx->c = 0;
	}
	ctx->valid = false;
}

char	**get_quote_dup(char *line)
{
	t_pipe_var	ctx;

	quote_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	while (ctx.end == 0)
	{
		if (*ctx.str == ctx.i && *ctx.str)
		{
			ctx.i = 0;
			ctx.quote = false;
			increment(&ctx);
		}
		if ((*ctx.str == '\'' || *ctx.str == '"') && ctx.i == 0)
		{
			ctx.i = *ctx.str;
			ctx.quote = true;
			increment(&ctx);
		}
		if (((*ctx.str == ' ') && ctx.quote == false)
			|| ft_strlen(ctx.str + 1) == 0)
			handle_quote_dup(&ctx);
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
