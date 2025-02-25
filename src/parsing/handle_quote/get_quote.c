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
	ctx->str = ft_pignouf(line);
	ctx->fstr = ctx->str;
}

void	get_word_init(t_quote *ctx, char *str, int j)
{
	str -= j;
	ctx->i = 0;
	ctx->c = 0;
	ctx->k = j;
	ctx->word = NULL;
	ctx->no_quote = false;
	ctx->quote = false;
	ctx->str = ft_strdup(str);
}

t_boolean	is_empty(char *str)
{
	char	*tmp;

	tmp = str;
	tmp -= 1;
	str -= 2;
	if (*str == '"' || *str == '\'')
	{
		if (*tmp == *str)
			return (true);
	}
	return (false);
}

void	quote_or_not(t_quote *ctx)
{
	char	*tmp;

	if (ctx->no_quote == true)
	{
		ctx->str--;
		tmp = ft_strndup(ctx->str, ctx->i - 1);
		ctx->word = ft_strjoin_custom(ctx->word, tmp);
		ctx->str -= ctx->i - 1;
		ctx->str = realloc_line(ctx->str, ctx->i + 1, NULL);
		ctx->no_quote = false;
		if ((*ctx->str == '"' || *ctx->str == '\''))
			ctx->c = *ctx->str;
	}
	else
	{
		tmp = ft_strndup(ctx->str, ctx->i - 1);
		ctx->word = ft_strjoin_custom(ctx->word, tmp);
		ctx->str++;
		ctx->k--;
		ctx->str = realloc_line(ctx->str, ctx->i + 1, NULL);
	}
}

void	handle_inside_quote(t_quote *ctx)
{
	char	*tmp;

	if (*ctx->str != '\'' && *ctx->str != '"')
	{
		tmp = ft_strndup(ctx->str, ctx->i);
		ctx->word = ft_strjoin_custom(ctx->word, tmp);
		ctx->str = realloc_line(ctx->str, ctx->i + 1, NULL);
		ctx->k--;
		//free tmp, free word
		ctx->c = 0;
	}
	else
	{
		quote_or_not(ctx);
	}
	tmp = NULL;
}

char	*extract_word(t_quote *ctx)
{
	char	*tmp;
	
	if (ctx->quote == false && ctx->i == 2 && is_empty(ctx->str))
	{
		fprintf(stderr, "empty\n");
		ctx->str = realloc_line(ctx->str, ctx->i, NULL);
		ctx->c = 0;
		return (ctx->word);
	}
	if (ctx->quote == false)
	{
		handle_inside_quote(ctx);
		return (ctx->word);
	}
	if (ctx->quote == true)
	{
		tmp = ft_strndup(ctx->str, ctx->i - 1);
		ctx->word = ft_strjoin_custom(ctx->word, tmp);
		ctx->str = realloc_line(ctx->str, ctx->i, NULL);
		//free tmp, free word
		return (ctx->word);
	}
	return (ctx->word);
}

void get_word_increment(t_quote	*ctx)
{
	ctx->k--;
	if (ctx->k >= 0)
	{
		ctx->str++;
		ctx->i++;
	}
}

char	*get_word(char *str, int j)
{
	t_quote	ctx;

	get_word_init(&ctx, str, j);
	while (ctx.k != -1 )
	{
		if (ctx.c == 0 && (*ctx.str == '"' || *ctx.str == '\''))
		{
			ctx.quote = true;
			ctx.c = *ctx.str;
			get_word_increment(&ctx);
			if (ctx.i > 1)
				ctx.no_quote = true;
		}
		if ((ctx.c == *ctx.str || ft_strlen(ctx.str) == 0 || ctx.no_quote == true))
		{
		fprintf(stderr, " IN word : '%s', newstr : '%s'\n", ctx.word, ctx.str);
			if (ctx.c == *ctx.str)
				ctx.quote = false;
			ctx.word = extract_word(&ctx);
			fprintf(stderr, "OUT word : '%s', newstr : '%s'\n", ctx.word, ctx.str);
		if (ctx.k == 0)
				break;
			ctx.i = 0;
		}
		else
			get_word_increment(&ctx);
	}
	fprintf(stderr, "word final: '%s'\n", ctx.word);
	return (ctx.word);
}

void	handle_quote(t_pipe_var *ctx)
{
	ctx->tmp = get_word(ctx->str, ctx->c);
	ctx->fstr = ctx->str;
	ctx->str -= ctx->c;
	ctx->str = realloc_line(ctx->str, ctx->c, &ctx->end);
	ctx->cmd_tab = realloc_add_to_tab(ctx->cmd_tab, ctx->tmp);
	ctx->c = 0;
	//free(ctx->fstr);
}

char	**get_quote_dup(char *line)
{
	t_pipe_var	ctx;

	quote_var_init(&ctx, line);
	if (!ctx.str)
		return (NULL);
	while (ctx.end == 0)
	{	
		if (ctx.i == 0 && (*ctx.str == '"' || *ctx.str == '\''))
		{
			ctx.i = *ctx.str;
			ctx.quote = true;
			increment(&ctx);
		}
		if (ctx.i == *ctx.str)
		{
			ctx.quote = false;
			ctx.i = 0;
		}
		if ((*ctx.str == ' ' && ctx.quote == false) || ft_strlen(ctx.str) == 0)
			handle_quote(&ctx);
		else
			increment(&ctx);
	}
	return (ctx.cmd_tab);
}
