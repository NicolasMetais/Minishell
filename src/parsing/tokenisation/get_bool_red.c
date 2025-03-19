/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bool_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:35:42 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/19 21:44:56 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	is_empty_file(char	*str)
{
	char	*tmp;

	str++;
	while (*str == ' ' || *str == '\'' || *str == '"')
	{
		if (*str == '\'' || *str == '"')
		{
			tmp = str + 1;
			if (*tmp == *str && ft_strlen(tmp + 1) == 0)
				return (true);
			if (*tmp == *str)
			{
				while (ft_strlen(tmp + 1) != 0 && (*tmp == *str))
					incr_empty_file(&tmp, &str);
				tmp--;
				if (*tmp == ' ' || ft_strlen(tmp + 1) == 0)
					return (true);
			}
			else
				break ;
		}
		str++;
	}
	return (false);
}

t_red	*new_red_value(t_bool_red *ctx)
{
	t_red	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		return (NULL);
	if (is_double(ctx->word))
	{
		ctx->word++;
		new->type = double_;
	}
	else
		new->type = simple;
	if (ctx->quote == true)
	{
		new->valid = false;
		new->empty_file = false;
	}
	else
	{
		new->valid = true;
		new->empty_file = is_empty_file(ctx->word);
	}
	new->next = NULL;
	new->error = false;
	return (new);
}

t_red	*add_back_red(t_red *red_value, t_red *new)
{
	t_red	*tmp;

	if (!red_value)
		return (new);
	tmp = red_value;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (red_value);
}

t_red	*get_bool(char *word, t_red *red_value, int *error)
{
	t_bool_red	ctx;
	t_red		*tmp;

	init_bool_red(&ctx, word);
	if (!ctx.word)
		return (NULL);
	while (*ctx.word)
	{
		turn_bool_red(&ctx);
		if (ft_strlen(ctx.word) == 0)
			break ;
		if (is_redirection_char(*ctx.word))
		{
			tmp = new_red_value(&ctx);
			if (!tmp)
			{
				*error = 1;
				return (free_tab_red(red_value), NULL);
			}
			red_value = add_back_red(red_value, tmp);
		}
		if (*ctx.word)
			ctx.word++;
	}
	return (free(ctx.tmp), red_value);
}

t_red	*get_tk_red(char *line, int *error)
{
	t_red	*red_value;

	red_value = NULL;
	red_value = get_bool(line, red_value, error);
	return (red_value);
}
