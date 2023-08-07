/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:12:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/06/09 10:40:28 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"

void	print_cmd_item(void *param);
char	*get_cmd_literal(void *param, int line);
void	print_env_item(void *param);
void	print_char_arr(char **arr);

#endif
