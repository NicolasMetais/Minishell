/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-02 10:38:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/02 15:14:28 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_line_failed(t_quote *ctx, t_free_var *f)
{
	free(f->word);
	free(ctx->word);
	free(f->str);
	ctx->word = NULL;
}

void	join_custom_failed(t_quote *ctx, t_free_var *f)
{
	free(f->word);
	free(f->tmp);
	free(f->str);
	ctx->word = NULL;
}

void	ndup_failed(t_quote *ctx, t_free_var *f)
{
	free(f->word);
	free(f->str);
	ctx->word = NULL;
}

void	quote_or_not_free(t_quote *ctx, t_free_var *f)
{
	free(f->word);
	free(f->str);
	f->str = NULL;
	f->word = NULL;
	ctx->tmp = ctx->str;
}

void	cmd_tab_handle_quote_failed(char **tmp, t_pipe_var *ctx)
{
	free_split(tmp);
	free(ctx->fstr);
	free(ctx->str);
	free(ctx->tmp);
	ctx->cmd_tab = NULL;
}
