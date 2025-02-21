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
	if (ft_strlen(s1) == 0)
		return ((char *)s2);
	if (ft_strlen(s2) == 0)
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

int		to_remove_begin(char *str)
{
	int	i;

	i = 0;
	while (*str != '"' && *str != '\'')
	{
		str++;
		i++;
	}
	return (i);
}

int		to_remove_end(char *str, int c)
{
	int		i;

	i = 0;
	str += c;
	while (*str != '"' && *str != '\'')
	{
		str--;
		i++;
	}
	return (i);
}

char	*remove_end(char *old, int c)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(old) - c;
	if (c > (int)ft_strlen(old))
		return (old);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (len >= 0)
	{
		new[i] = *old;
		i++;
		len--;
		old++;
	}
	new[i] = '\0';
	return (new);
}

char	*remove_begin(char *old, int c)
{
	char	*new;
	size_t		i;
	size_t		len;
	
	old += c;
	i = 0;
	len = ft_strlen(old);
	new = malloc(sizeof(char) * ft_strlen(old) + 1);
	if (!new)
		return (NULL);

	while (i < len)
	{
		new[i] = *old;
		old++;
		i++;
	}
	new[i] = '\0';
	return (new);
}