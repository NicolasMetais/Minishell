/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:33:29 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/03 17:47:31 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(const char *nptr)
{
	int				i;
	long long		res;
	int				bol;

	res = 0;
	i = 0;
	bol = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		bol = 1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10;
		res = res + (nptr[i] - '0');
		i++;
	}
	if (bol == 1)
		res = res * (-1);
	return (res);
}
