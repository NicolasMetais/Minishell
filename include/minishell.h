/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 05:08:17 by nmetais           #+#    #+#             */
/*   Updated: 2025/01/31 06:28:08 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED_LIGHT "\033[91m"


# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

void	funny_stuff(void);
void	signal_handler(void);
#endif