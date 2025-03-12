/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_replace_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:25:42 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/12 03:58:25 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//JE DELETE LA VAR SI ELLE EXISTE PAS ET JE RECONSTRUIS LA STRING SANS LA VAR
char	*delete_var(char *tocut, int start, int end)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * ((ft_strlen(tocut) - end + 1)));
	if (!new)
		return (NULL);
	j = 0;
	i = 0;
	while (tocut[j])
	{
		if (j == start)
			j += end;
		if (j >= (int)ft_strlen(tocut))
			break ;
		new[i] = tocut[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

//J'ECRIT LA VAR A LA PLACE DU $VAR
char	*write_var(char *code, char *tocut, int j, int size)
{
	char	*new;
	int		i;
	int		l;
	int		k;

	i = 0;
	l = 0;
	k = 0;
	new = malloc(sizeof(char) * (ft_strlen(code)
				+ (ft_strlen(tocut) - size) + 1));
	if (!new)
		return (NULL);
	while (tocut[i])
	{
		if (i == j)
		{
			while (code[k])
				new[l++] = code[k++];
			i += size;
		}
		else
			new[l++] = tocut[i++];
	}
	new[l] = '\0';
	return (new);
}

void	rewrite_line(t_core *core, int arg_nb, int count)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	printf("LEN %zu\n ARG NB %d\n COUNT %d\n", ft_strlen(core->line), arg_nb, count);
	if (arg_nb == 0 || count == 0)
    	return ;
	free(core->line);
	core->line = malloc(sizeof(char) * (count + (arg_nb - 1) + 1));
	if (!core->line)
		return ;
	while (core->new_line[++i])
	{
		j = -1;
		while (core->new_line[i][++j])
			core->line[k++] = core->new_line[i][j];
		if (core->new_line[i + 1] != NULL)
			core->line[k++] = ' ';
	}
	core->line[k] = '\0';
}
