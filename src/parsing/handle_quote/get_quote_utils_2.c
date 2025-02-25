/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-20 16:29:31 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-20 16:29:31 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_custom(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;

	i = 0;
	if (ft_strlen(s1) == 0 && !s1)
		return ((char *)s2);
	if (ft_strlen(s2) == 0 && !s2)
		return ((char *)s1);
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
