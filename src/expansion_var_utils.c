/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 22:43:51 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-15 22:43:51 by jbayonne         ###   ########.fr       */
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

char	*dynamic_copy(char *old, char c)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(old);
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(old);
	return (new);
}

void	get_variable_incr(int *i, t_core *core)
{
	(*i) += 1;
	core->line++;
}
