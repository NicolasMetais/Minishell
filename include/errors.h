/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmetais <nmetais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 02:14:11 by nmetais           #+#    #+#             */
/*   Updated: 2025/02/09 17:49:51 by nmetais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

//ERROR MODULABLE PROTECTED FUNCTIONS
t_boolean	invalid_option(t_builtin *builtin, char *cmd);
t_boolean	too_many_args(char *cmd);
t_boolean	cmd_not_found(char *cmd);
int			only_num_arg(t_builtin *builtin, char *cmd);
//PERROR MODULABLE
t_boolean	funct_error(char *cmd, char *addvalue);

#endif