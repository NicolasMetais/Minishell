/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:25:25 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/18 01:25:34 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s)
{
	char	*buffer;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	buffer = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!buffer)
		return (NULL);
	while (s[i])
	{	
		buffer[i] = s[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
