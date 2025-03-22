/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bool_red_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:46:21 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/19 21:48:41 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_true_pipe_bool(t_bool_pipe *ctx)
{
	ctx->c = *ctx->word;
	ctx->quote = true;
	ctx->word++;
}

void	turn_false_pipe_bool(t_bool_pipe *ctx)
{
	ctx->quote = false;
	ctx->c = 0;
	ctx->word++;
}

void	turn_pipe_bool(t_bool_pipe *ctx)
{
	if (*ctx->word == ctx->c)
		turn_false_pipe_bool(ctx);
	if (ctx->c == 0 && (*ctx->word == '"' || *ctx->word == '\''))
		turn_true_pipe_bool(ctx);
}

void	turn_bool_red(t_bool_red *ctx)
{
	if (*ctx->word == ctx->c)
	{
		turn_false_get_bool(ctx);
	}
	if (ctx->c == 0 && (*ctx->word == '"' || *ctx->word == '\''))
	{	
		turn_true_get_bool(ctx);
	}
	if (*ctx->word == ctx->c)
	{
		turn_false_get_bool(ctx);
	}
}

void	turn_token_error(t_bool_pipe *var)
{
	if (*var->word == var->c)
		turn_false_tok_error(var);
	if (var->c == 0 && (*var->word == '\'' || *var->word == '"'))
		turn_true_tok_error(var);
}
