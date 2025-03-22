/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quote_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:15:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/08 21:57:03 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_line_handle_quote_failed(t_pipe_var *ctx)
{
	free_split(ctx->cmd_tab);
	free(ctx->fstr);
	free(ctx->tmp);
	ctx->cmd_tab = NULL;
}

void	get_word_failed(t_pipe_var *ctx)
{
	if (ctx->cmd_tab)
		free_split(ctx->cmd_tab);
	ctx->cmd_tab = NULL;
	if (ctx->fstr)
		free(ctx->fstr);
}

void	reset_handle_quote(t_pipe_var *ctx)
{
	if (ft_strlen(ctx->str) == 1 && (*ctx->str == '"' || *ctx->str == '\''))
	{
		free(ctx->str);
		free_split(ctx->cmd_tab);
		ctx->cmd_tab = NULL;
		ctx->end = 1;
	}
	ctx->c = 0;
	free(ctx->fstr);
	ctx->fstr = NULL;
}

void	quote_or_not_free(t_quote *ctx, t_free_var *f)
{
	free(f->word);
	free(f->str);
	if (ctx->k == 0)
	{	
		free(ctx->str);
	}
	f->str = NULL;
	f->word = NULL;
	ctx->tmp = ctx->str;
}
