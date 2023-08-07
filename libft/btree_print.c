/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:36:05 by albertvanan       #+#    #+#             */
/*   Updated: 2023/05/05 22:34:15 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree_print.h"

/**
 * @brief Print the data from a given node and the spaces surrounding it
 * 
 * @param node the node from which the data must be printed
 * @param spaces the amount of spaces before and after the node data (determined
 * by the depth)
 * @param w the width of the data to be displayed
 * @param c2c the function to be used to turn the void *content of the node to 
 * a char* with the data the user wants to see
 */
static void	print_node(t_btnode *node, t_btp_vars vars, int line)
{
	char	*cont_str;

	if (node)
	{
		print_chars((vars.spaces - 1) * vars.width, " ");
		if (vars.spaces > 0)
			print_chars(vars.width / 2, " ");
		cont_str = vars.content2char(node->content, line);
		if (cont_str == NULL)
			ft_printf("\e[48;5;019m│%*.*s│\e[0m", vars.width - 2, \
											vars.width - 2, "ERROR");
		else
			ft_printf("\e[48;5;019m│%*.*s│\e[0m", vars.width - 2, \
												vars.width - 2, cont_str);
		free(cont_str);
		if (vars.spaces > 0)
			print_chars(vars.width / 2, " ");
		print_chars((vars.spaces - 1) * vars.width, " ");
	}
	else
	{
		print_chars((vars.spaces * 2 - 1) * vars.width, " ");
		print_chars(vars.width, " ");
	}
}

/**
 * @brief Print the lines representing the relation from a node
 * to its children.
 * 
 * @param node the nod
 * @param spaces the amount of space between nodes
 * @param width the width each node gets to display its data
 */
static void	print_branch(t_btnode *node, int spaces, int width)
{
	if (node->left)
	{
		ft_printf("┌");
		print_chars((spaces * width) / 2 - 1, "─");
	}
	else
		print_chars((spaces * width) / 2, " ");
	if (node->left && node->right)
		ft_printf("┴");
	else if (node->left)
		ft_printf("┘");
	else if (node->right)
		ft_printf("└");
	if (node->right)
	{
		print_chars((spaces * width) / 2 - 1, "─");
		ft_printf("┐");
	}
	else
		print_chars((spaces * width) / 2, " ");
}

/**
 * @brief Prints spaces of no child node is present,
 * calls print_branch if the branch-lines to a child node
 * must be printed.
 * 
 * @param node the node which relations must be printed
 * @param vars	struct with vars, used are:
 	* @param spaces the amount of spaces between nodes (is determined
 	* by the depth)
 	* @param width the width each node gets to display its data 
 */
static void	print_lines(t_btnode *node, t_btp_vars vars)
{
	if (node)
	{
		print_chars((vars.spaces * vars.width) / 2, " ");
		if (node->left == NULL && node->right == NULL)
			print_chars(vars.width * vars.spaces + 1, " ");
		else
			print_branch(node, vars.spaces, vars.width);
		print_chars((vars.spaces * vars.width) / 2 - 1, " ");
	}
	else
		print_chars(vars.spaces * vars.width * 2, " ");
}

/**
 * @brief Norminette-induced function-split. Called by ft_btree_print and does
 * the actual work: one outer loop (depth), with two inner loops (the nodes), one
 * for the nodes' content, the other for the lines representing the branch 
 * relations.
 * 
 * @param bt_arr the array to be printed
 * @param depth the depth of the binary tree
 * @param c2c the function used to transform the nodes' content to a char*
 * @param w the width of the char* to be displayed
 */
static void	print_bt_arr(void ***bt_arr, int depth, t_btp_vars vars)
{
	int		d_i;
	int		w_i;
	int		l_i;
	int		positions;

	d_i = 0;
	while (d_i < depth)
	{
		vars.spaces = ft_pow(2, depth - 1) / ft_pow(2, d_i + 1);
		positions = ft_pow(2, d_i);
		l_i = 0;
		while (l_i < vars.lines)
		{
			w_i = 0;
			while (w_i < positions)
				print_node((t_btnode *)bt_arr[d_i][w_i++], vars, l_i);
			ft_printf("\n");
			l_i++;
		}
		w_i = 0;
		while (w_i < positions)
			print_lines((t_btnode *)bt_arr[d_i][w_i++], vars);
		ft_printf("\n");
		d_i++;
	}
}

/**
 * @brief Prints a binary tree with the root on top and the leaves on their
 * respective level downwards.
 * 
 * @param root the root of the binary tree
 * @param content2char a function that returns whatever you want displayed of
 * the void *content of the binary tree node as a malloc'ed char*. The print 
 * function will free this pointer for you. The lines parameter determines the
 * amount of lines printed, this should be the same across the function call
 * of ft_btree_print and in this function. Every time content2char is called
 * the line parameter will increase by one, starting from 0. Branch/switch 
 * accordingly in this function.
 * @param width the width of the content information to be displayed. Set small 
 * for binary trees with a large depth, as the bottom line of the printed binary 
 * tree will be [width * 2^depth-1] (irrespectful of the amount of nodes actually
 * present on this depth, this can be 1 through 2^depth-1)
 * @param lines the amount of lines printed for each node. Should be the same 
 * across the function call and in the content2char switch/branching.
 */
void	ft_btree_print(t_btnode *root, char *(*content2char)(void *, int), \
														int width, int lines)
{
	int			depth;
	void		***btree_arr;
	t_btp_vars	vars;

	depth = ft_btree_get_depth(root);
	btree_arr = init_btree_arr(depth);
	vars.width = width;
	vars.lines = lines;
	vars.content2char = content2char;
	if (btree_arr == NULL)
		return ;
	btree_to_arr(root, 0, 0, btree_arr);
	print_bt_arr(btree_arr, depth, vars);
	while (depth-- > 0)
		free(btree_arr[depth]);
	free(btree_arr);
}
