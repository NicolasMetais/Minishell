/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:43:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:35:17 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!buffer)
		return (NULL);
	while (*s1 && s1)
	{
		buffer[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 && s2)
	{	
		buffer[i] = *s2;
		s2++;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

/*
int	main(void)
{
	char	*s1 = "Salut ";
	char	*s2 = "les gens";
	char 	*buffer;

	buffer = ft_strjoin(s1, s2);
}*/
