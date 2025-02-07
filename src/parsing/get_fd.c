/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-06 14:21:03 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-06 14:21:03 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Gestion des redirections


fd_init() initialise toutes les variables qui concernent les files.

Les files descriptors sont a -2 pour ne pas confondre en cas d'erreur d'ouverture.
fd_..[1] correspond a la redirection 1 = > | <, 2 = >> | <<. Ils sont a 0 si il n'y a pas de redirection.
Si ils sont superieur a 2 on detecte une rreur de saisie */

void	fd_init(t_cmd *cmd)
{
	cmd->in_fd[0]= -2;
	cmd->in_fd[1]= 0;
	cmd->out_fd[0] = -2;
	cmd->out_fd[1] = 0;
}

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

/*get_infd recupere un infile et le type de redirection de la commande
char **cmd_split est le tableau de la commande entiere.

ex : < chips cat -e 
"<"
"chips"
"cat"
"-e"

on par court le tableau en comparant n caractere de la string pour voir si la string
corrspond a une redirection. Si la string correspond a une redirectin, on ouvre la string
d,a
*/

int	get_infd(t_cmd *cmd, char **cmd_split)
{
	int	i;
	
	i = 0;
	while (cmd_split[i])
	{
		if (ft_strncmp(cmd_split[i], "<", 1) == 0 
			|| ft_strncmp(cmd_split[i], "<<", 2) == 0)
		{
				cmd->in_fd[0] = open_file(cmd_split[i + 1]);
				cmd->in_fd[0] = ft_strlen(cmd_split[i]);
		}
		i++;
	}
}

int	get_outfd(t_cmd *cmd, char **cmd_split)
{
	int	i;
	
	i = 0;
	while (cmd_split[i])
	{
		if (ft_strncmp(cmd_split[i], ">", 1) == 0 
			|| ft_strncmp(cmd_split[i], ">>", 2) == 0)
		{
				cmd->out_fd[0] = open_file(cmd_split[i + 1]);
				cmd->out_fd[0] = ft_strlen(cmd_split[i]);
        }
		i++;
	}
}

void	get_fd(t_cmd *cmd, char **cmd_line_split)
{
	fd_init(cmd);
	get_fd_in(cmd, cmd_line_split);
	get_fd_out(cmd, cmd_line_split);
}