/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-16 07:50:50 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-16 07:50:50 by jbayonne         ###   ########.fr       */
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
	ctx->str = ft_strdup(line);
	ctx->fstr = ctx->str;
}

void	handle_quote_dup(t_pipe_var *ctx)
{
	if (ctx->quote == false || ft_strlen(ctx->str + 1) == 0)
	{
		if (ft_strlen(ctx->str + 1) == 0)
		{
			ctx->str++;
			ctx->tmp = ft_strndup(ctx->str, ctx->c + 1);
		}
		else
			ctx->tmp = ft_strndup(ctx->str, ctx->c);
		ctx->cmd_tab = realloc_add_to_tab(ctx->cmd_tab, ctx->tmp);
		ctx->str -= ctx->c;
		ctx->str = realloc_line(ctx->str, ctx->c + 1, &ctx->end);
		ctx->c = 0;
	}
	ctx->valid = false;
}

char	*remove_quote(char *str)
{
	size_t		i;
	int			j;
	char		*new;
	
	i = 0;
	j = 1;
	new = malloc(sizeof(char) * ft_strlen(str) - 1);
	if (!new)
		return (NULL);
	while (i < ft_strlen(str) - 2)
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	**clear_quote(char	**cmd)
{
	char	**clear_cmd;
	char	*tmp;
	int		i;

	clear_cmd = NULL;
	i = 0;
	while (cmd[i])
	{
		if (is_in_quote(cmd[i]))
			tmp = remove_quote(cmd[i]);
		else
			tmp = ft_strdup(cmd[i]);
		clear_cmd = realloc_add_to_tab(clear_cmd, tmp);
		i++;
	}
	free_split(cmd);
	return (clear_cmd);
}

char	**get_quote_dup(char *line)
{
	t_pipe_var	ctx;

	quote_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	while (ctx.end == 0)
	{
		if (*ctx.str == ctx.i && *ctx.str)
		{
			ctx.i = 0;
			ctx.quote = false;
			increment(&ctx);
		}
		if ((*ctx.str == '\'' || *ctx.str == '"') && ctx.i == 0)
		{
			ctx.i = *ctx.str;
			ctx.quote = true;
			increment(&ctx);
		}
		if ((*ctx.str == ' ' && ctx.quote == false)
			|| ft_strlen(ctx.str + 1) == 0)
			handle_quote_dup(&ctx);
		else
			increment(&ctx);
	}
	return (free(ctx.fstr), clear_quote(ctx.cmd_tab));
}
