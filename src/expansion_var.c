/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 02:10:30 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/26 11:03:21 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_utils(char *old, t_core *core, int i)
{
	char	*var;
	char	*tmp;
	char	*new;

	tmp = ft_strndup(core->line, i);
	if (!tmp)
		return (free(old), NULL);
	if (*tmp == '?')
	{
		var = ft_itoa(core->exit_code);
		if (!var)
			return (NULL);
	}
	else
		var = ft_get_env(core->env, tmp);
	free(tmp);
	new = ft_strjoin_custom(old, var);
	free(var);
	if (!new)
		return (free(old), NULL);
	return (new);
}

char	*get_variable(char *old, t_core *core, t_tk_dollar *dollar)
{
	char	*new;
	int		i;

	i = 0;
	core->line++;
	if (dollar->valid == true && (ft_isalpha(*core->line) || *core->line == '_'
			|| *core->line == '?'))
	{
		if (*core->line == '?')
			get_variable_incr(&i, core);
		else
		{
			while (*core->line && (ft_isalnum(*core->line)
					|| *core->line == '_'))
				get_variable_incr(&i, core);
		}
		new = get_variable_utils(old, core, i);
		if (!new)
			return (NULL);
		return (free(old), new);
	}
	else
		core->line--;
	return (old);
}

char	*get_new_line(t_expand_var *ctx, t_core *core, t_tk_dollar **dollar)
{
	char	*new;

	if (*core->line == '$')
		*dollar = (*dollar)->next;
	new = dynamic_copy(ctx->new_line, *core->line);
	if (!new)
		return (free(ctx->tmp), NULL);
	core->line++;
	return (new);
}

char	*expansion_var(t_core *core)
{
	t_expand_var	ctx;

	init_var_expand(&ctx, core);
	if (ctx.error == 1)
		return (NULL);
	while (*core->line)
	{
		ctx.tmp = ctx.new_line;
		if (*core->line == '$' && ctx.dollar->valid == true)
		{
			ctx.new_line = get_variable(ctx.new_line, core, ctx.dollar);
			if (!ctx.new_line)
				return (free(ctx.tmp), free_tk_dollar(ctx.tmp_d), NULL);
			ctx.dollar = ctx.dollar->next;
		}
		else
		{
			ctx.new_line = get_new_line(&ctx, core, &ctx.dollar);
			if (!ctx.new_line)
				return (free(ctx.tmp), free_tk_dollar(ctx.tmp_d), NULL);
		}
	}
	if (ctx.tmp_d)
		core->exit_code = 0;
	return (free_tk_dollar(ctx.tmp_d), ctx.new_line);
}
