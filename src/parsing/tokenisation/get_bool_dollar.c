/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bool_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:09:57 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:33:29 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tk_dollar	*new_dollar_value(t_get_dollar_bool ctx)
{
	t_tk_dollar	*new;
	char		c;

	c = 0;
	new = malloc(sizeof(t_tk_dollar));
	if (!new)
		return (NULL);
	if (ft_strlen(ctx.line) == 1)
	{
		new->valid = false;
		new->next = NULL;
		return (new);
	}
	ctx.line++;
	set_new_tk_dollar_as_valid(new, ctx);
	new->next = NULL;
	return (new);
}

t_tk_dollar	*add_back_dollar(t_tk_dollar *dollar_value, t_tk_dollar *new)
{
	t_tk_dollar	*tmp;

	if (!dollar_value)
		return (new);
	tmp = dollar_value;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (dollar_value);
}

void	get_bool_tk_dollar_incr(t_get_dollar_bool *ctx)
{
	if (*ctx->line != '\'' && *ctx->line != '"')
	{
		ctx->line++;
		ctx->k++;
	}
}

t_tk_dollar	*get_bool_tk_dollar(char *str, t_tk_dollar *dollar, int *error)
{
	t_get_dollar_bool	ctx;

	init_get_dollar_bool(&ctx, str);
	while (*ctx.line)
	{
		if ((ctx.c_simp == 0 && *ctx.line == '\'')
			|| (ctx.c_db == 0 && *ctx.line == '"'))
			get_bool_dollar_turn_true(&ctx);
		if (*ctx.line == ctx.c_db || *ctx.line == ctx.c_simp)
			get_bool_dollar_turn_false(&ctx);
		if (!*ctx.line)
			break ;
		if (*ctx.line == '$')
		{
			ctx.tmp = new_dollar_value(ctx);
			if (!ctx.tmp)
			{
				(*error) = 1;
				return (NULL);
			}
			dollar = add_back_dollar(dollar, ctx.tmp);
		}
		get_bool_tk_dollar_incr(&ctx);
	}
	return (dollar);
}

t_tk_dollar	*get_tk_dollar(char *line, int *error)
{
	t_tk_dollar	*dollar;
	t_tk_dollar	*tmp;

	dollar = NULL;
	dollar = get_bool_tk_dollar(line, dollar, error);
	tmp = dollar;
	while (tmp)
		tmp = tmp->next;
	return (dollar);
}
