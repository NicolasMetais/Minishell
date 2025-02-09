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

/* Command_counter compte le nombre de commande stocke dans le char **line_split. 
La memoire de **line_split est allouee dans global_init() par ft_split(read_line, '|'). */

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

/*open_file() est appele dans get_infd() et get_outfd() pour ouvrir les fichiers de redirection.
Si le fichier ne s'ouvre pas, le message d'erreur s'affiche mais le programme continue. 

La commande n'est pas ajoutee a la liste fd = -1.*/

int		open_file(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, file, ft_strlen(file));
		perror("");
	}
	return (fd);
}