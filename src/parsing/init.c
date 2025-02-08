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

void	add_back(t_cmd *head, t_cmd *new)
{
	t_cmd	*tmp;

	if (head == NULL)
	{
		head = new;
		tmp = NULL;
		return ;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	tmp = NULL;
	return ;
}

int	search_cmd(char **all_path, char **cmd)
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
		while (cmd[j])
		{
			while (is_redirection(cmd[j]))
				j += 2;
			cmd_path = ft_strjoin(one_path, cmd[j]);
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (free(one_path), j);
			free(cmd_path);
			j++;
		}
		free(one_path);
		i++;
	}
	return (-1);
}

char	**get_cmd(char **cmd_line_split, char **all_path)
{
	char	**cmd;
	int		i_cmd;
	int		i;

	i = 0;
	i_cmd = search_cmd(all_path, cmd_line_split);
	if (i_cmd == -1)
		return (cmd_line_split);
	cmd = malloc(sizeof(char *) * (command_counter(cmd_line_split) + 1));
	if (!cmd)
		return (NULL);
	while (i < command_counter(cmd_line_split))
	{
		if (i == 0)
			cmd[i] = ft_strdup(cmd_line_split[i_cmd]);
		else
			cmd[i] = 
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
	cmd->path = get_path(cmd_line_split, all_path);
	get_fd(cmd, cmd_line_split);
	cmd->cmd = get_cmd(cmd_line_split, all_path);
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

void	check_and_add_cmd_to_list(t_cmd *head, t_cmd *tmp)
{
		if (tmp->in_fd[0] == -1 || tmp->out_fd[0] == -1)
		{
			free_node(tmp);
			return ;
		}
		if (tmp->in_fd[1] > 2 || tmp->out_fd[1] > 2)
		{
			free_node(tmp);
			// ajouter une gestion d'erreur (ex : ">>>>>" token not found blablabla)
			return;
		}
		else
			add_back(head, tmp);
}

t_cmd   *set_cmd(char **line_split, char **env)
{
	t_cmd	*head;
	t_cmd	*tmp;
	int		i;

	i = 0;		
	head = new_cmd(line_split[i], env);
	if (!head)
		return (NULL);
	i++;
	while (line_split[i])
	{
		tmp = new_cmd(line_split[i], env);
		if (!tmp)
			return (freelist(head), NULL);
		check_and_add_cmd_to_list(head, tmp);
		i++;
	}
	return (head);
}

void    global_init(t_glb *glb, char *read_line, char **env)
{
	char	**line_split;

	line_split = ft_split(read_line, '|');
	if (!line_split)
		return ;
	glb = malloc(sizeof(t_glb));
	if (!glb)
		return ;
	glb->nb_cmd = command_counter(line_split);
	glb->path = get_all_path(env);
	glb->cmd = set_cmd(line_split, glb->path);
}
