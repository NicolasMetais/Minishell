/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bool_dollar_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 20:32:28 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-15 20:32:28 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_get_dollar_bool(t_get_dollar_bool *ctx, char *str)
{
	ctx->c_simp = 0;
	ctx->c_db = 0;
	ctx->quote = false;
	ctx->line = str;
}

void	get_bool_dollar_turn_true(t_get_dollar_bool *ctx)
{
	if (*ctx->line == '\'')
		ctx->c_simp = *ctx->line;
	else
		ctx->c_db = *ctx->line;
	if (ctx->c_simp != 0 && ctx->c_db == 0)
		ctx->quote = true;
	ctx->line++;
}

void	get_bool_dollar_turn_false(t_get_dollar_bool *ctx)
{
	if (*ctx->line == '\'')
		ctx->c_simp = 0;
	else
		ctx->c_db = 0;
	if (ctx->c_simp == 0)
		ctx->quote = false;
	ctx->line++;
}
