/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 02:14:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/03/22 16:02:52 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "boolean.h"
# include "parsing.h"

//ERROR MODULABLE PROTECTED FUNCTIONS
t_boolean	invalid_option(t_cmd *cmd_tab, char *cmd, t_core *core);
t_boolean	too_many_args(char *cmd, t_core *core);
t_boolean	cmd_not_found(char *cmd, t_core *core);
t_boolean	only_num_arg(t_cmd *cmd_tab, char *cmd, t_core *core);
int			not_valid_id(char *arg, char *cmd, t_core *core);
int			env_not_set(char *arg, char *cmd, t_core *core);
t_boolean	permission_denied(char *cmd, t_core *core);
t_boolean	error_directory(char *cmd, t_core *core);

//PERROR MODULABLE
t_boolean	funct_error(char *cmd, char *addvalue, t_core *core);
t_boolean	is_a_file(char *str);
t_boolean	file_name_argument(char *cmd, t_core *core);
t_boolean	only_point(char *str);

// EXEC
void		execve_error(t_core *core, t_exec *exec, char *tmp);

#endif