/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bool_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:27:17 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-10 14:27:17 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_bool_pipe(t_bool_pipe *ctx, char *line)
{
	ctx->word = ft_strdup(line);
	ctx->tmp = ctx->word;
	ctx->quote = false;
	ctx->c = 0;
}

t_pipe_token	*new_pipe_value(t_bool_pipe *ctx)
{
	t_pipe_token	*new;

	new = malloc(sizeof(t_red));
	if (!new)
		return (NULL);
	if (ctx->quote == true)
		new->valid = false;
	else
		new->valid = true;
	new->next = NULL;
	return (new);
}

t_pipe_token	*add_back_pipe(t_pipe_token *pipe_value, t_pipe_token *new)
{
	t_pipe_token	*tmp;

	if (!pipe_value)
		return (new);
	tmp = pipe_value;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (pipe_value);
}

t_pipe_token	*get_bool_pipe(char *word, t_pipe_token *pipe_value, int *error)
{
	t_bool_pipe			ctx;
	t_pipe_token		*tmp;

	init_bool_pipe(&ctx, word);
	if (!ctx.word)
		return (NULL);
	while (*ctx.word)
	{
		turn_pipe_bool(&ctx);
		if (*ctx.word == '|')
		{
			tmp = new_pipe_value(&ctx);
			if (!tmp)
			{
				*error = 1;
				return (free_pipe_tk(pipe_value), NULL);
			}
			pipe_value = add_back_pipe(pipe_value, tmp);
		}
		if (*ctx.word)
			ctx.word++;
	}
	return (free(ctx.tmp), pipe_value);
}

t_pipe_token	*get_tk_pipe(char *line, int *error)
{
	t_pipe_token	*pipe_value;

	pipe_value = NULL;
	pipe_value = get_bool_pipe(line, pipe_value, error);
	return (pipe_value);
}
