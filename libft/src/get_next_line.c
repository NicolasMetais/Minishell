/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:48:37 by jbayonne          #+#    #+#             */
/*   Updated: 2025/03/22 20:40:01 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../../include/minishell.h"
#include <fcntl.h>

char	*ft_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
		return (str);
	}
	else
	{
		str = NULL;
		return (str);
	}
}

static int	is_line(char *read, char *buffer)
{
	int	i;

	if (len(buffer) == 0 && len(read) != 0)
		return (1);
	i = 0;
	while (read[i])
	{
		if (read[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_search_line(char *buffer, char *next_line, ssize_t i)
{
	static char	*read;

	next_line = 0;
	read = ft_read_init(buffer, read, i);
	if (i < 0)
		return (ft_free(next_line), ft_free(read));
	if (!read)
		return (ft_free(next_line));
	if (!is_line(read, buffer))
	{
		if (len(read) == 0)
			read = ft_free(read);
		return (NULL);
	}
	else
		next_line = ft_next_line_init(read);
	if (!next_line)
		return (NULL);
	read = ft_read_update(read, next_line);
	if (!read)
		return (ft_free(next_line), ft_free(read));
	if (len(read) == 0)
		read = ft_free(read);
	return (next_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	char		*buffer;
	ssize_t		i;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (i != 0)
	{	
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			ft_search_line(0, next_line, i);
			return (ft_free(buffer));
		}
		buffer[i] = '\0';
		next_line = ft_search_line(buffer, next_line, i);
		if (!(!next_line))
			return (ft_free(buffer), next_line);
		next_line = ft_free(next_line);
	}
	return (ft_free(buffer));
}

/*
int	main(void)
{
	char	*s;
	int		fd;

	fd = open("test", O_RDONLY);
	s = get_next_line(fd);

	free(s);

	return (0);
}*/
