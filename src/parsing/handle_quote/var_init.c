/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 10:31:24 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/03 21:30:03 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_var_init(t_pipe_var *ctx, char *line)
{
	ctx->c = 0;
	ctx->i = 0;
	ctx->end = 0;
	ctx->cmd_tab = NULL;
	ctx->valid = false;
	ctx->quote = false;
	ctx->str = ft_pignouf(line);
	//
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
