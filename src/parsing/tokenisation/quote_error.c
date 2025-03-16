/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 17:00:42 by jbayonne          #+#    #+#             */
/*   Updated: 2025-03-15 17:00:42 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_error_turn_true(t_boolean *in, int *db, int *simp, char str)
{
	if (str == '\'')
		*simp += 1;
	else
		*db += 1;
	*in = true;
}

void	quote_error_turn_false(t_boolean *in, int *db, int *simp, char str)
{
	if (str == '\'')
		*simp += 1;
	else
		*db += 1;
	*in = false;
}

t_boolean	quote_error_bis(int db, int simp)
{
	if (simp % 2 != 0)
	{
		printf("minishell: missing closing quote`''\n");
		return (true);
	}
	if (db % 2 != 0)
	{
		printf("minishell: missing closing quote`\"'\n");
		return (true);
	}
	return (false);
}

t_boolean	quote_error(char *str)
{
	char		c;
	int			db;
	int			simp;
	t_boolean	in;

	c = 0;
	simp = 0;
	db = 0;
	in = false;
	while (*str)
	{
		if (c == 0 && (*str == '\'' || *str == '"'))
		{
			quote_error_turn_true(&in, &db, &simp, *str);
			c = *str;
			str++;
		}
		if (*str == c)
		{
			quote_error_turn_false(&in, &db, &simp, *str);
			c = 0;
		}
		if (*str)
			str++;
	}
	return (quote_error_bis(db, simp));
}
