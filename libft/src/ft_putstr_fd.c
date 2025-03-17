/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:06:07 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/17 00:30:36 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &*s, 1);
		s++;
	}
}

/*
int	main(void)
{
	int		fd;
	char 	*str = "Salut la team";
	
	fd = open("chips", O_WRONLY);
	if (fd == -1)
		return (0);
	ft_putstr_fd(str, fd);
	return (0);
}*/
