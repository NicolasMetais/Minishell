/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:50:10 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 01:35:00 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stddef.h>

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr_c;
	int		i;

	i = ft_strlen(s);
	ptr_c = 0;
	while (c > 255)
		c = c -256;
	if (c == 0)
		return ((char *)&s[i]);
	while (*s)
	{
		if (ft_strchr(s, c))
			ptr_c = (char *)s;
		s++;
	}
	return (ptr_c);
}

/*
int	main(void)
{
	const char	*str = "";
	int			c = '\n';


}
*/
