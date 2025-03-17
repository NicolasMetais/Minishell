/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:22:01 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:35:04 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <bsd/string.h> 

size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = 0;
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && little[j])
					j++;
		if (j + i <= len && little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	if (ft_strlen(little) < 1)
		return ((char *)big);
	else
		return (ptr);
}

/*
int	main(void)
{
	char	*big = "aaxx";
	char	*little = "xx";
	char 	*ptr;
	char	*ptr1;

	ptr = ft_strnstr(big, little, 5);
	ptr1 = strnstr(big, little, 5);
	
}*/
