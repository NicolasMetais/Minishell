/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 06:12:32 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/05 06:49:15 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_env	t_env;
typedef struct s_core	t_core;
typedef enum s_boolean	t_boolean;

typedef struct s_cd
{
	char		*pwd;
	char		*oldpwd;
	char		*home;
	t_boolean	undo;
	t_boolean	ishome;
	t_boolean	previous;
	int			prev_count;
}	t_cd;

t_boolean	builtin(t_core *core);
void		env_var(t_core *core);
void		exit_status_display(t_core *core);
void		cd(t_core *core);
void		cmd_exec(t_core *core);
void		cd_parsing(t_core *core);

#endif