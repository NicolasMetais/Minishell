/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inside_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-21 18:01:35 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-21 18:01:35 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mid_inside_quote(t_in_quote *ctx, char *old)
{
	int		len;
	char	*tmp;
	char	*new;

	tmp = NULL;
	len = 0;
	len = to_remove_begin(ctx->str);
	tmp = get_begin(ctx->str, len);
	if (tmp)
		ctx->str = remove_begin(ctx->str, len);
	new = ft_strjoin(old, tmp);
	if (*ctx->str == '"' || *ctx->str == '\'')
	{
		ctx->type = *ctx->str;
		ctx->str++;
		ctx->i++;
	}
	return (new);
}

void	update_inside_quote_data(t_in_quote *ctx)
{
	ctx->str -= ctx->i;
	ctx->str = remove_begin(ctx->str, ctx->i);
	ctx->i = 0;
	ctx->type = 0;
}

char	*empty_inside_quote(t_in_quote *ctx)
{
	char	*new;
	char	*tmp;
	
	tmp = NULL;
	new = NULL;
	ctx->str++;
	if (ft_strlen(ctx->str) == 0)
	{
		fprintf(stderr, "ici\n");
		return (ctx->str);
	}
	if (*ctx->str != '"' && *ctx->str != '\'')
	{
		tmp = get_begin(ctx->str, to_remove_begin(ctx->str));
		if (tmp)
			ctx->str = remove_begin(ctx->str,  to_remove_begin(ctx->str));
		new = ft_strjoin_custom(ctx->mid, tmp);
		if (!new)
			return (NULL);
		ctx->type = 0;
	}
	else
	{
		ctx->type = *ctx->str;
		fprintf(stderr, "ctx->type : %c | ctx->str : %c\n",ctx->type, *ctx->str);
	}
	if (!new)
		new = ctx->str;
	fprintf(stderr, "new : %s\n", ctx->str);
	return (new);
}

char	*handle_inside_quote(t_in_quote *ctx)
{
	char	*str;

	if (ctx->i == 0)
	{
		str = empty_inside_quote(ctx);
		return (str);
	}
	str = ft_strnjoin(ctx->mid, ctx->str, ctx->i);
	if (!str)
		return (NULL);
	update_inside_quote_data(ctx);
	if (*ctx->str == '"' || *ctx->str == '\'')
	{
		ctx->type = *ctx->str;
		ctx->str++;
		if (*ctx->str == '"' || *ctx->str == '\'')
			ctx->type = *ctx->str;
	}
	if (*ctx->str != '"' && *ctx->str != '\''
		&& ft_strlen(ctx->str) != 0 && *ctx->str != ' ')
		str = mid_inside_quote(ctx, str);
	return (str);
}
