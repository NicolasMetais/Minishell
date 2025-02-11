/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 12:52:44 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-07 12:52:44 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_counter(char **line_split)
{
	int	i;

	i = 0;
	while (line_split[i])
		i++;
	return (i);
}

t_boolean	is_redirection(char	*s)
{
	if (ft_strncmp(s, "<", 1) == 0)
		return (true);
	if (ft_strncmp(s, "<<", 1) == 0)
		return (true);
	if (ft_strncmp(s, ">", 1) == 0)
		return (true);
	if (ft_strncmp(s, ">>", 1) == 0)
		return (true);
	return (false);
}

int	open_file_in(char *file)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, file, len);
		write(2, " : ", 3);
		perror("");
	}
	return (fd);
}

int	open_file_out(char	*file, int i)
{
	int	fd;

	fd = 0;
	if (i != 2)
	{
		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
		{
			write(2, file, ft_strlen(file));
			write(2, " : ", 3);
			perror("");
		}
	}
	else
	{
		fd = open(file, O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
		{
			write(2, file, ft_strlen(file));
			write(2, " : ", 3);
			perror("");
		}
	}
	return (fd);
}
