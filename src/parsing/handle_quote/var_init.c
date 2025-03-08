/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-02 10:31:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-02 10:31:24 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	quote_var_init(t_pipe_var *ctx, char *line)
{
	ctx->c = 0;
	ctx->i = 0;
	ctx->end = 0;
	ctx->cmd_tab = NULL;
	ctx->valid = false;
	ctx->quote = false;
	ctx->str = ft_pignouf_prime(line);
	fprintf(stderr, "STR : '%s'\n", ctx->str);
	ctx->fstr = ctx->str;
}

void	get_word_init(t_quote *ctx, char *str, int j)
{
	str -= j;
	ctx->i = 0;
	ctx->c = 0;
	ctx->k = j;
	ctx->word = NULL;
	ctx->no_quote = false;
	ctx->quote = false;
	ctx->str = ft_strdup(str);
	ctx->tmp = ctx->str;
	ctx->first = ctx->str;
}
