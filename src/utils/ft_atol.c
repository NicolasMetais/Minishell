/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:33:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 15:54:42 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_atol
{
	int				i;
	long			res;
	int				sign;
	int				digit;
}	t_atol;

long long	ft_atol(const char *nptr)
{
	t_atol	atol;

	atol.res = 0;
	atol.i = 0;
	atol.digit = 0;
	atol.sign = 1;
	while ((nptr[atol.i] >= '\t' && nptr[atol.i] <= '\r')
		|| nptr[atol.i] == ' ')
		atol.i++;
	if (nptr[atol.i] == '+' || nptr[atol.i] == '-')
	{
		if (nptr[atol.i++] == '-')
			atol.sign = -1;
	}
	while (nptr[atol.i] && nptr[atol.i] >= '0' && nptr[atol.i] <= '9')
	{
		atol.digit = nptr[atol.i++] - '0';
		if (atol.sign == 1 && (atol.res > (LONG_MAX - atol.digit) / 10))
			return (LONG_MAX);
		if (atol.sign == -1 && (atol.res > (LONG_MIN + atol.digit) / -10))
			return (LONG_MIN);
		atol.res = atol.res * 10 + atol.digit;
	}
	return (atol.res * atol.sign);
}
