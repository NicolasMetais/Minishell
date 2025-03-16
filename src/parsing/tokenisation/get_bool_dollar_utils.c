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
	ctx->c = 0;
	ctx->quote = false;
	ctx->line = str;
}

void	get_bool_dollar_turn_true(t_get_dollar_bool *ctx)
{
	printf("turn true\n");
	ctx->quote = true;
	ctx->c = *ctx->line;
	ctx->line++;
}

void	get_bool_dollar_turn_false(t_get_dollar_bool *ctx)
{
	printf("turn false\n");
	ctx->quote = false;
	ctx->c = 0;
	ctx->line++;
}
