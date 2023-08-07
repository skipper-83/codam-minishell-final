/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:29:37 by albertvanan       #+#    #+#             */
/*   Updated: 2023/04/30 23:08:54 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

/**
 * @brief Create new node
 * 
 * @param content void pointer to content
 * @param left pointer to left child
 * @param right pointer to right child
 * @return t_btnode* the new node, NULL on error
 */
t_btnode	*ft_btnode_new(void	*content, t_btnode *left, t_btnode *right)
{
	t_btnode	*res;

	res = malloc(sizeof(t_btnode));
	if (res == NULL)
		return (NULL);
	res->content = content;
	res->left = left;
	res->right = right;
	return (res);
}

/**
 * @brief Add a node as the new root to the tree pointed to by [root]
 * 
 * @param root the root of the tree
 * @param new_root the node that will be the new root
 * @param dir [left / right] the side the old root will be attached to
 */
void	ft_btnode_add_as_root(t_btnode **root, t_btnode *new_root, t_dir dir)
{
	t_btnode	*buf;

	buf = *root;
	*root = new_root;
	if (dir == left)
		(*root)->left = buf;
	else if (dir == right)
		(*root)->right = buf;
}

/**
 * @brief Iterete over a tree (left - self - right) and execute the function f
 * on the nodes' content.
 * 
 * @param root the root of the tree
 * @param f the function to be performed
 * @param depth used in recursion, should be 0 when called
 */
void	ft_btree_iter(t_btnode *root, void (*f)(void *, int depth), int depth)
{
	if (root == NULL)
		return ;
	ft_btree_iter(root->left, f, depth + 1);
	f(root->content, depth);
	ft_btree_iter(root->right, f, depth + 1);
}

/**
 * @brief Add a node as a leaf to the node passed as branch
 * 
 * @param branch the node that will be the parent of the new node
 * @param new the new node
 * @param dir [left/right] the side to which the node will be attached
 */
void	ft_btnode_add_as_leaf(t_btnode *branch, t_btnode *new, t_dir dir)
{
	if (dir == left)
		branch->left = new;
	else if (dir == right)
		branch->right = new;
}

/**
 * @brief Free a binary tree, use 'f' to free the nodes' content.
 * 
 * @param root the tree
 * @param f function to free the nodes' content.
 */
void	ft_btree_free(t_btnode **root, void (*f)(void *))
{
	if (*root == NULL)
		return ;
	ft_btree_free(&(*root)->left, f);
	ft_btree_free(&(*root)->right, f);
	if (f != NULL)
		f((*root)->content);
	free(*root);
	*root = NULL;
}
