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
	ctx->k = 0;
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
	ctx->k++;
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
	ctx->k++;
}

void	set_new_tk_dollar_as_valid(t_tk_dollar *new, t_get_dollar_bool ctx)
{
	char c;

	c = 0;
	if (ctx.k >= 2)
	{
		ctx.line -= 2;
		c = *ctx.line;
		ctx.line += 2;
	}
	if (ctx.quote == true)
		new->valid = false;
	else if (*ctx.line == ' ')
		new->valid = false;
	else if (*ctx.line == '$')
		new->valid = false;
	else if (c == '\'' && *ctx.line == '\'')
		new->valid = false;
	else if (!ft_isalpha(*ctx.line) && *ctx.line != '_' && *ctx.line != '?')
		new->valid = false;
	else
		new->valid = true;
}
