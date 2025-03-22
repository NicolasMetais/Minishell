/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:43:41 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:35:49 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*bytes_dest;
	unsigned char	*bytes_src;
	size_t			i;

	if (!dest && !src)
		return (0);
	i = 0;
	bytes_dest = (unsigned char *) dest;
	bytes_src = (unsigned char *) src;
	while (i < n)
	{
		bytes_dest[i] = bytes_src[i];
		i++;
	}
	return (dest);
}

/*
int	main(void)
{
//	char	str[10] ="013456789";
//	char	*dest = "0000000000";

	int		arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int		*arr1;

	arr1 = 0;
	
	arr1 = memcpy(arr1, arr, sizeof(int) * 10);	
	for (int i = 0; arr[i]; i++)	

	arr1 = ft_memcpy(arr1, arr, sizeof(int) * 10);	
	for (int i = 0; arr[i]; i++)	

}*/
