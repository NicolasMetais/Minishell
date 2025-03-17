/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:10 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:35:55 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*block;
	char			*ptr;
	unsigned char	i;

	ptr = 0;
	i = (unsigned char) c;
	block = (unsigned char *) s;
	while (n--)
	{
		if (*block == i)
			return (block);
		block++;
	}
	return (ptr);
}

/*
int main(void)
{
	const int arr[11] = {0,1,2,5,4,5,6,7,8,85};
	const	char *str = "Je suis une array de char";
	int c = -97;
	int a = 85;


}*/
