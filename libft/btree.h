/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:28:33 by albertvanan       #+#    #+#             */
/*   Updated: 2023/05/05 22:37:26 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "libft.h"

typedef struct s_btnode
{
	void			*content;
	struct s_btnode	*left;
	struct s_btnode	*right;
}	t_btnode;

typedef enum e_dir
{
	left,
	right
}	t_dir;

t_btnode	*ft_btnode_new(void	*content, t_btnode *left, t_btnode *right);
void		ft_btnode_add_as_root(t_btnode **r, t_btnode *new_root, t_dir dir);
void		ft_btree_iter(t_btnode *r, void (*f)(void *, int depth), int depth);
void		ft_btnode_add_as_leaf(t_btnode *branch, t_btnode *new, t_dir dir);
void		ft_btree_free(t_btnode **root, void (*f)(void *));

int			ft_btree_get_depth(t_btnode *root);
int			ft_btree_count_nodes(t_btnode *root);

void		ft_btree_print(t_btnode *root, char *(*content2char)(void *, int), \
														int width, int lines);

#endif