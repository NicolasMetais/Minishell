/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bool_red_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:56:04 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/20 16:52:40 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_double(char *word)
{
	char	c;

	c = *word;
	word++;
	if (*word == c)
		return (true);
	return (false);
}

void	turn_true_get_bool(t_bool_red *ctx)
{
	ctx->c = *ctx->word;
	ctx->quote = true;
	ctx->word++;
}

void	turn_false_get_bool(t_bool_red *ctx)
{
	ctx->quote = false;
	ctx->c = 0;
	if (ft_strlen(ctx->word) != 0)
		ctx->word++;
}

void	init_bool_red(t_bool_red *ctx, char *word)
{
	ctx->error.error = true;
	ctx->error.next = NULL;
	ctx->error.type = simple;
	ctx->error.valid = false;
	ctx->word = ft_strdup(word);
	ctx->tmp = ctx->word;
	ctx->quote = false;
	ctx->c = 0;
}

int	bool_len(int *bool)
{
	int	i;

	i = 0;
	while (bool[i])
		i++;
	return (i);
}
