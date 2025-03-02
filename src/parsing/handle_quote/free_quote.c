/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-02 10:38:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/02 13:44:29 by jbayonne         ###   ########.fr       */
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
	ctx->tmp = ctx->str;
}
