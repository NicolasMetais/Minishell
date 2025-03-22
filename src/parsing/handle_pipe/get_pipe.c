/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 07:50:50 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 16:45:53 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	turn_false_pipe(t_pipe_var *ctx)
{
	ctx->i = 0;
	ctx->quote = false;
	increment(ctx);
}

char	**get_pipe(char *line)
{
	t_pipe_var	ctx;

	pipe_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	while (ctx.end == 0)
	{
		if (ctx.str && (*ctx.str == ctx.i && *ctx.str))
			turn_false_pipe(&ctx);
		if (ctx.str && ((*ctx.str == '\'' || *ctx.str == '"') && ctx.i == 0))
		{
			ctx.i = *ctx.str;
			ctx.quote = true;
		}
		if ((*ctx.str == '|' && ctx.quote == false)
			|| ft_strlen(ctx.str) == 0)
		{
			handle_pipe(&ctx);
			if (!ctx.cmd_tab)
				return (NULL);
		}
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
