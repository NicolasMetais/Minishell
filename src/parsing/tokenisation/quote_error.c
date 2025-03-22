/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:00:42 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 02:12:54 by nmetais          ###   ########.fr       */
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
	t_blue		var;
	t_boolean	in;

	c = 0;
	var.simp = 0;
	var.db = 0;
	in = false;
	while (*str)
	{
		if (c == 0 && (*str == '\'' || *str == '"'))
		{
			quote_error_turn_true(&in, &var.db, &var.simp, *str);
			c = *str;
			str++;
		}
		if (*str == c)
		{
			quote_error_turn_false(&in, &var.db, &var.simp, *str);
			c = 0;
		}
		if (*str)
			str++;
	}
	return (quote_error_bis(var.db, var.simp));
}
