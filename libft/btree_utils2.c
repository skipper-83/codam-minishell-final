/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:33:13 by albertvanan       #+#    #+#             */
/*   Updated: 2023/04/05 23:13:53 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

/**
 * @brief Get the depth of a binary tree
 * 
 * @param root the binary tree
 * @return int the depth of the given tree as int
 */
int	ft_btree_get_depth(t_btnode *root)
{
	int	left_depth;
	int	right_depth;

	if (root == NULL)
		return (0);
	left_depth = ft_btree_get_depth(root->left);
	right_depth = ft_btree_get_depth(root->right);
	return (ft_max(right_depth, left_depth) + 1);
}

/**
 * @brief Count all nodes in a tree
 * 
 * @param root the tree whose nodes need counting
 * @return int the amount of nodes as int
 */
int	ft_btree_count_nodes(t_btnode *root)
{
	int	left_count;
	int	right_count;

	if (root == NULL)
		return (0);
	left_count = ft_btree_count_nodes(root->left);
	right_count = ft_btree_count_nodes(root->right);
	return (left_count + right_count + 1);
}
