/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quet_quote_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-20 19:08:38 by jbayonne          #+#    #+#             */
/*   Updated: 2025-02-20 19:08:38 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pignouf(char *line)
{
	t_pignouf	var;

	var.i = 0;
	var.j = 0;
	var.len = ft_strlen(line) - 1;
	while (line[var.i] == ' ')
		var.i++;
	while (line[var.len] == ' ')
	{
		var.len--;
		var.j++;
	}
	var.new = malloc(sizeof(char) * (ft_strlen(line) - (var.i + var.j)) + 1);
	if (!var.new)
		return (NULL);
	var.j = 0;
	while (var.i <= var.len)
	{
		var.new[var.j] = line[var.i];
		var.i++;
		var.j++;
	}
	var.new[var.j] = '\0';
	return (var.new);
}
