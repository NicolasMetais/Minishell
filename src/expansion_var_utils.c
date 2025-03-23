/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:43:51 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/23 16:22:40 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tk_dollar(t_tk_dollar *dollar)
{
	t_tk_dollar	*tmp;

	while (dollar)
	{
		tmp = dollar->next;
		free(dollar);
		dollar = NULL;
		dollar = tmp;
	}
}

void	init_var_expand(t_expand_var *ctx, t_core *core)
{
	ctx->error = 0;
	ctx->tmp = NULL;
	ctx->new_line = NULL;
	ctx->dollar = get_tk_dollar(core->line, &ctx->error);
	ctx->tmp_d = ctx->dollar;
}

void	get_variable_incr(int *i, t_core *core)
{
	(*i) += 1;
	core->line++;
}

t_boolean	env_parse(t_core *core)
{
	rotate_env(core, "PATH");
	core->path = ft_strdup(core->env->var);
	if (!core->path)
		return (false);
	core->splitted_path = ft_split(core->path, ':');
	if (!core->splitted_path)
		return (false);
	free(core->path);
	return (true);
}
