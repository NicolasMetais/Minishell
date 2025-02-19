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

t_boolean	pipe_valid(char *line)
{
	char	*tmp;

	tmp = line;
	if (*line != '\0')
		line++;
	while (*line && *line == ' ')
		line++;
	if (*line == '|')
		return (false);
	return (true);
}

void	pipe_var_init(t_pipe_var *ctx, char *line)
{
	ctx->c = 0;
	ctx->i = 0;
	ctx->end = 0;
	ctx->cmd_tab = NULL;
	ctx->valid = false;
	ctx->quote = false;
	ctx->str = ft_strdup(line);
	ctx->fstr = ctx->str;
}

void	handle_pipe(t_pipe_var *ctx)
{
	if (!pipe_valid(ctx->str))
		return ;
	if (ctx->quote == false || ft_strlen(ctx->str + 1) == 0)
	{
		if (ft_strlen(ctx->str + 1) == 0)
		{
			ctx->str++;
			ctx->tmp = ft_strndup(ctx->str, ctx->c + 1);
		}
		else
			ctx->tmp = ft_strndup(ctx->str, ctx->c);
		ctx->cmd_tab = realloc_add_to_tab(ctx->cmd_tab, ctx->tmp);
		ctx->str -= ctx->c;
		ctx->str = realloc_line(ctx->str, ctx->c + 1, &ctx->end);
		free(ctx->fstr);
		ctx->fstr = ctx->str;
		ctx->c = 0;
	}
	ctx->valid = false;
}

void	increment(t_pipe_var *ctx)
{
	ctx->str++;
	ctx->c++;
}

char	**get_pipe(char *line)
{
	t_pipe_var	ctx;

	pipe_var_init(&ctx, line);
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
		}
		if ((*ctx.str == '|' && ctx.quote == false)
			|| ft_strlen(ctx.str + 1) == 0)
			handle_pipe(&ctx);
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
