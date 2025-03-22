/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quet_quote_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-20 19:08:38 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-20 19:08:38 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_custom(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;

	i = 0;
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buffer)
		return (free((char *)s1), NULL);
	while (*s1)
	{
		buffer[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{	
		buffer[i] = *s2;
		s2++;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

t_boolean	is_empty(char *str)
{
	char	*tmp;

	tmp = str;
	tmp -= 1;
	if (*str == '"' || *str == '\'')
	{
		if (*tmp == *str)
			return (true);
	}
	return (false);
}

void	free_var_init(t_quote *ctx, t_free_var *f)
{
	f->str = ctx->str - ctx->i;
	f->word = ctx->word;
	f->tmp = NULL;
}

void	get_word_increment(t_quote	*ctx)
{
	ctx->k--;
	if (ctx->k >= 0)
	{
		ctx->str++;
		ctx->i++;
	}
}
