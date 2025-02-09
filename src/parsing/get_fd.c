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
#include "parsing.h"
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

/*get_infd() recupere un infile et le type de redirection de la commande
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

// aucune gestion d'erreur pour l'instant

char	**get_infd(t_cmd *cmd, char **cmd_split)
{
	int	i;
	
	i = 0;
	while (cmd_split[i])
	{
		if (ft_strncmp(cmd_split[i], "<", 1) == 0 
			|| ft_strncmp(cmd_split[i], "<<", 2) == 0)
		{
			if (ft_strlen(cmd_split[i]) == 2)
			{
				if (cmd->here_doc != NULL)
					free(cmd->here_doc);
				cmd_split = realloc_cmd(cmd_split, i);
				if (!cmd_split)
					return (NULL);
				cmd->here_doc = ft_strdup(cmd_split[i + 1]);
				if (!cmd->here_doc)
					return (NULL);
				cmd_split = realloc_cmd(cmd_split, i + 1);
				if (!cmd_split)
					return (NULL);
				return (cmd_split);
			}
			else
			{	
				cmd_split = realloc_fd_in(cmd, cmd_split, i);
				if (!cmd_split)
					return (NULL);
				return (cmd_split);
			}
		}
		i++;
	}
	return (cmd_split);
}

/*get_outfd() marche comme get_out fd pour la redirection out*/

char 	**get_outfd(t_cmd *cmd, char **cmd_split)
{
	int	i;
	
	i = 0;

	while (cmd_split[i])
	{
		if (ft_strncmp(cmd_split[i], ">", 1) == 0 
			|| ft_strncmp(cmd_split[i], ">>", 2) == 0)
		{
			if (!realloc_fd_out(cmd, cmd_split, i))
				return (NULL);
		}
		i++;
	}
	return (cmd_split);
}

char	**get_fd(t_cmd *cmd, char **cmd_line_split)
{
	char **tmp;

	fd_init(cmd);
	cmd->here_doc = NULL;
	tmp = get_infd(cmd, cmd_line_split);
	if (!cmd_line_split)
		return (NULL);
	cmd_line_split = get_outfd(cmd, tmp);
	if (!cmd_line_split)
		return (NULL);
	return (cmd_line_split);
}