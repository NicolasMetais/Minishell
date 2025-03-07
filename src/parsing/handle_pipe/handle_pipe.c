/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-03 17:43:20 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-03 17:43:20 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe_realloc_line_and_tab(t_pipe_var *ctx, char **tmp)
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
}

void	handle_pipe_get_cmd(t_pipe_var *ctx)
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

void	handle_pipe(t_pipe_var *ctx)
{
	char	**tmp;

	tmp = ctx->cmd_tab;
	if (!pipe_valid(ctx->str))
		return ;
	if (ctx->quote == false || ft_strlen(ctx->str + 1) == 0)
	{
		handle_pipe_get_cmd(ctx);
		if (!ctx->tmp)
			exit (-1); // pb de malloc
		handle_pipe_realloc_line_and_tab(ctx, tmp);
		if (ctx->cmd_tab == NULL)
			return ;
		free(ctx->fstr);
		ctx->fstr = ctx->str;
		ctx->c = 0;
	}
	ctx->tmp = NULL;
	ctx->valid = false;
}
