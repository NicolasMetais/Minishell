/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:09:17 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:35:11 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>

size_t	ft_strlen(const char *str);

size_t	ft_strlcpy(char *dest, const char *src, size_t siz)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (siz == 0)
		return (len);
	while (src[i] && siz -1)
	{
		dest[i] = src[i];
		i++;
		siz--;
	}
	dest[i] = '\0';
	return (len);
}

/*
int	main(void)
{
	char *str = "0123456";
	char dst[100];
	char *str1 = "0123456";
	char dst1[100];
	
}*/
