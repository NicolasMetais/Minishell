/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quote_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:15:56 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/02 16:26:50 by jbayonne         ###   ########.fr       */
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
	free_split(ctx->cmd_tab);
	ctx->cmd_tab = NULL;
	free(ctx->str - ctx->c);
	if (ctx->fstr)
		free(ctx->fstr);
}

void	reset_handle_quote(t_pipe_var *ctx)
{
	free(ctx->tmp);
	ctx->c = 0;
	free(ctx->fstr);
	ctx->fstr = NULL;		
}
