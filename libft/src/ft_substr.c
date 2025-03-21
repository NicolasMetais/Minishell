/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:29:02 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:34:53 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

size_t	ft_strlen(char const *s);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub;
	size_t				i;
	unsigned int		l;

	i = 0;
	l = ft_strlen(s);
	if (start >= l)
		len = 0;
	if (len > l - start)
		len = l - start;
	sub = malloc((sizeof(char) * (len + 1)));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

/*
int	main(void)
{
	char	*s;

	s = ft_substr("hola", 0, 18446744073709551615);
	free(s);
	return (0);
}*/
