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

void	handle_pipe_1(t_pipe_var *ctx)
{
	if (ft_strlen(ctx->str) == 1)
	{
		ctx->str++;
		ctx->tmp = ft_strndup(ctx->str, ctx->c + 1);
		if (!ctx->tmp)
		{
			free(ctx->str - ctx->c - 1);
			free_split(ctx->cmd_tab);
			ctx->cmd_tab = NULL;
			return ;
		}
	}
	else
	{
		ctx->tmp = ft_strndup(ctx->str, ctx->c);
		if (!ctx->tmp)
		{
			free(ctx->str - ctx->c);
			free_split(ctx->cmd_tab);
			ctx->cmd_tab = NULL;
			return ;
		}
	}
}

void	handle_pipe_2(t_pipe_var *ctx)
{
	ctx->cmd_tab = realloc_add_to_tab(ctx->cmd_tab, ctx->tmp);
	if (!ctx->cmd_tab)
	{
		free_split(tmp);
		free(ctx->str - ctx->c);
		return ;
	}
	ctx->str -= ctx->c;
	ctx->str = realloc_line(ctx->str, ctx->c + 1, &ctx->end);
	if (!ctx->str)
	{
		free(ctx->fstr);
		free_split(ctx->cmd_tab);
		ctx->cmd_tab = NULL;
		return ;
	}
	free(ctx->fstr);
	ctx->fstr = ctx->str;
	ctx->c = 0;
}

void	handle_pipe(t_pipe_var *ctx)
{
	char	**tmp;

	tmp = ctx->cmd_tab;
	if (!pipe_valid(ctx->str))
		return ;
	if (ctx->quote == false || ft_strlen(ctx->str + 1) == 0)
	{
		handle_pipe_1(ctx);
		if (ctx->cmd_tab == NULL)
			return ;
		handle_pipe_2(ctx);		
		if (ctx->cmd_tab == NULL)
			return ;
	}
	if (ctx->tmp)
		free(ctx->tmp);
	ctx->tmp = NULL;
	ctx->valid = false;
}

void	increment(t_pipe_var *ctx)
{
	ctx->str++;
	ctx->c++;
}

void	get_pipe_turn_false(t_pipe_var *ctx)
{
	ctx.i = 0;
	ctx.quote = false;
	increment(ctx);
}

char	**get_pipe(char *line)
{
	t_pipe_var	ctx;

	pipe_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	while (ctx.end == 0)
	{
		if (ctx.str && (*ctx.str == ctx.i && *ctx.str))
			get_pipe_turn_false(&ctx);
		if (ctx.str && ((*ctx.str == '\'' || *ctx.str == '"') && ctx.i == 0))
		{
			ctx.i = *ctx.str;
			ctx.quote = true;
		}
		if ((*ctx.str == '|' && ctx.quote == false)
			|| ft_strlen(ctx.str) == 1)
		{
			handle_pipe(&ctx);
			if (ctx.cmd_tab == NULL)
				return (NULL);
		}
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
