/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:32:30 by albertvanan       #+#    #+#             */
/*   Updated: 2023/05/23 23:17:24 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Add subtree to node. The root of a subtree can be an operator,
 * 			so it needs its own subfunction to be added, else the function will
 * 			assume it is an operator in a non-prioritized command stream and
 * 			mess up the subtree.
 * 			This function gets called when the *previous* command has the
 * 			is_subtree flag high, so this command is the root of
 * 			the subtree, and the current command is the next operator to be added.
 * 			If there is a last operator, the current operator will be put to the 
 * 			right branch of it, while the subtree previously on that right branch 
 * 			will be the left branch of the current operator. Like so:
 * 
 * 	`					&&
 * 					/		 \
 * 					cmd1	subtree
 * 
 * 					becomes
 * 
 * 						&&
 * 					/		 \
 * 					cmd1	 &&
 * 						   /    \
 * 					     subtree `
 * 
 * 			Alternatively, if the current command is the first operator in the stream,
 * 			the subtree will be added to the left branch this operator only. (yes this 
 * 			can be written with a few lines less)
 * 
 * @param last 
 * @param cur 
 * @param prev 
 */
void	add_subtree(t_btnode **last, t_btnode *cur, t_btnode **prev)
{
	if (*last != NULL)
	{
		cur->left = (*last)->right;
		(*last)->right = cur;
		*last = cur;
	}
	else
	{
		cur->left = *prev;
		*last = cur;
	}
}

/**
 * @brief	Add leaf to tree.
 * 			If left branch of last node is open then the current node is
 * 			an operator:
 * 			-> if there is no previous operator, add current node
 * 				to left branch
 * 			-> if there is a current last operator, swap the right node
 * 				of the last operator with the current operator, and 
 * 				add the right node previously attached to the last operator
 * 				to the current operator. So:
 * 						&&
 * 					/		 \
 * 					cmd1	cmd2
 * 
 * 					becomes
 * 
 * 						&&
 * 					/		 \
 * 					cmd1	 &&
 * 						   /    \
 * 					     cmd2
 * 
 * @param prev	the previous noude
 * @param last	the last operator
 * @param cur 	the current node
 * @param r		the rood of the tree
 */
void	add_leaf(t_btnode **prev, t_btnode **last, t_btnode *cur, t_btnode **r)
{
	if ((*prev)->left == NULL)
	{
		if (*last == NULL && ((t_cmd *)(*prev)->content)->type && *r == NULL)
		{
			(*prev)->left = cur;
			*last = *prev;
			*r = *prev;
		}
		else if (*last == NULL)
			cur->left = *prev;
		else
		{
			cur->left = (*last)->right;
			(*last)->right = cur;
			*last = cur;
		}
	}
	else if ((*prev)->right == NULL)
	{
		(*prev)->right = cur;
		*last = *prev;
		if (*r == NULL)
			*r = *prev;
	}
}

/**
 * @brief	Subfunction for make_command_tree and make_command_subtree
 * 			Sets 'previous' to current node if previous is null or instead
 * 			adds current node as leaf or subtree (depending on the
 * 			subtree flag) to the previous node.
 * 
 * @param cur	the current node
 * @param root 	the root of the tree, passed as double pointer so it can be 
 * 				altered
 * @param last	the last operator encountered
 * @param prev	the previous node
 * @return int	1 on success, 0 on error, throws its own error msgs
 */
int	tree_loop(t_btnode *cur, t_btnode **root, t_btnode **last, t_btnode **prev)
{
	t_cmd	*prev_command;

	if (cur == NULL)
		return (ft_btree_free(root, NULL), mem_error(), 0);
	if (*prev != NULL)
	{
		prev_command = (t_cmd *)(*prev)->content;
		if (prev_command->is_subtree)
			add_subtree(last, cur, prev);
		else
			add_leaf(prev, last, cur, root);
	}
	*prev = cur;
	return (1);
}

/**
 * @brief	Called when a ( is encountered by make_command_(sub)tree. Makes a
 * 			subtree of the part between brackets and returns the root of this
 * 			subtree
 * 
 * @param command	t_list with command structs, passed as double pointer so
 * 					the caller function can proceed where this function has
 * 					lef off
 * @param work		t_list item with start position of list, used as the work pointer
 * 					when browsing throug the list
 * @return t_btnode*	root of subtree or NULL on error (NB subtree 
 * 						flag is set high)
 */
static t_btnode	*make_command_subtree(t_list **command, t_list *work)
{
	t_btnode	*root;
	t_btnode	*current;
	t_btnode	*previous;
	t_btnode	*last_operator;

	previous = NULL;
	root = NULL;
	last_operator = NULL;
	while (work)
	{
		if (((t_cmd *)work->content)->type == BRO)
			current = make_command_subtree(&work, work->next);
		else
			current = ft_btnode_new(work->content, NULL, NULL);
		if (!tree_loop(current, &root, &last_operator, &previous))
			return (NULL);
		work = work->next;
		if (((t_cmd *)work->content)->type == BRC)
			break ;
	}
	*command = work;
	if (root == NULL)
		root = current;
	((t_cmd *)root->content)->is_subtree = 1;
	return (root);
}

/**
 * @brief	Takes a t_list with t_cmd structs and puts it into 
 * 			a binary tree
 * 
 * @param command	the t_list with command structs
 * @return t_btnode*	the root of the binary tree, or NULL on error
 */
t_btnode	*make_command_tree(t_list *command)
{
	t_btnode	*root;
	t_btnode	*current;
	t_btnode	*previous;
	t_btnode	*last_operator;

	previous = NULL;
	root = NULL;
	last_operator = NULL;
	while (command)
	{
		if (((t_cmd *)command->content)->type == BRO)
			current = make_command_subtree(&command, command->next);
		else
			current = ft_btnode_new(command->content, NULL, NULL);
		if (!tree_loop(current, &root, &last_operator, &previous))
			return (NULL);
		command = command->next;
	}
	if (root == NULL)
		root = current;
	return (root);
}
