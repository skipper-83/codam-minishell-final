/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:35:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/06/08 12:51:35 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_PRINT_H
# define BTREE_PRINT_H

# include "btree.h"

typedef struct s_btree_print_vars
{
	int		width;
	int		lines;
	int		spaces;
	char	*(*content2char)(void *, int lines);
}	t_btp_vars;

void	***init_btree_arr(int depth);
void	print_chars(int amount, char *c);
void	btree_to_arr(t_btnode *root, int depth, int id, void ***btree_arr);

#endif