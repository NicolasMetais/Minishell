/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-05 13:32:09 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-05 13:32:09 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_all_path(char **env)
{
	int		i;
	char	*s;
	char	**env_path;

	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")) == 0)
		{
			s = env[i];
			break ;
		}
		i++;
	}
	s += 5;
	env_path = ft_split(s, ';');
	if (!env_path)
		return (NULL);
	return (env_path);
}

char	*get_path(char **cmd_line_split, char **all_path)
{
	char	*cmd_path;
	char	*one_path;
	int		i;
	int		j;

	i = 0;
	while (all_path[i])
	{
		j = 0;
		one_path = ft_strjoin(all_path[i], "/");
		while (cmd_line_split[j])
		{
			cmd_path = ft_strjoin(one_path, cmd_line_split[j]);
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (cmd_path);
			free(cmd_path);
			j++;
		}
		free(one_path);
		i++;
	}
}

t_cmd   *new_cmd(char *line_split, char **all_path)
{
	t_cmd   *cmd;
	char	**cmd_line_split;

	cmd_line_split = ft_split(line_split, ' ');
	if (!cmd_line_split)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	get_fd(cmd, cmd_line_split);
	cmd->path = get_path(cmd_line_split, all_path);
	cmd->next = NULL;
	free_split(cmd_line_split);
	return (cmd);
}

/* set_cmd() cree la liste chaine de commande.

(ex : "< chips cat | wc -l", Ici on a deux commande "< chip cat" et "wc -l")

char **line_split correspond au tableau de commande initialise dans
global_init() avec ft_split.

nb correspond on nombre total de commande renvoyer par command_count dans 
global_init().

Donc on itere sur chaque membre de notre tableau de commande ou chaque commande
est un index. A chaque commande on cree un node qu'on ajoute a la liste avec add_back.

cf new_cmd pour l'initialisation des nodes src/parsing/initialisation.c .
*/

t_cmd   *set_cmd(char **line_split, char **env)
{
	t_cmd	*head;
	t_cmd	*tmp;
	int		i;

	i = 0;		
	head = new_cmd(line_split[i], env);
	i++;
	while (line_split[i])
	{
		tmp = new_cmd(line_split[i], env);
		if (!tmp || tmp->in_fd[0] == -1 || tmp->out_fd[0] == -1)
		{
			free_node(tmp);
		}
		add_back(head, tmp);
		i++;
	}
}

void    global_init(t_glb *glb, char *read_line, char **env)
{
	char	**line_split;

	line_split = ft_split(read_line, '|');
	if (!line_split)
		return ;
	glb->nb_cmd = command_count(read_line);
	glb->path = get_all_path(env);
	glb->cmd = set_cmd(read_line, glb->path);
}  