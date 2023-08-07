/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 22:40:50 by albertvanan       #+#    #+#             */
/*   Updated: 2023/04/05 22:57:31 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree_print.h"

/**
 * @brief	Initialize two dimensional array of void pointers. Use power of 2
 * 			for size per depth, so depth 0 = size 2^0, depth 1 is size 2^1, etc
 * 
 * @param depth depth of binary tree
 * @return void*** returns void***, NULL on error
 */
void	***init_btree_arr(int depth)
{
	void	***ret;
	int		i;

	ret = ft_calloc(depth, sizeof(void **));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < depth)
	{
		ret[i] = ft_calloc(ft_pow(2, i), sizeof(void *));
		if (ret[i] == NULL)
			break ;
		i++;
	}
	if (i != depth)
	{
		while (--i >= 0)
			free(ret[i]);
		free(ret);
		return (NULL);
	}
	return (ret);
}

/**
 * @brief Print the character string c amount times
 * 
 * @param amount 
 * @param c 
 */
void	print_chars(int amount, char *c)
{
	int	i;

	if (amount < 1)
		return ;
	i = 0;
	while (i < amount)
	{
		ft_printf("%s", c);
		i++;
	}
}

/**
 * @brief Used by btree_to_arr. For every depth, delete the offset so the
 * first index of the array for any given depth (btree_array[depth]) is 0.
 * 
 * 
 * @param depth the given depth
 * @return int the offset
 */
static int	get_id_offset(int depth)
{
	if (depth < 2)
		return (0);
	if (depth == 2)
		return (1);
	return (ft_pow(2, depth - 1) - 1 + get_id_offset(depth - 1));
}

/**
 * @brief Put a binary tree in a two dimensional void* array.
 * 
 * @param root root of binary tree
 * @param depth used for recursion, set to 0 when calling the function
 * @param id  used for recursion, set to 0 when calling the function
 * @param btree_arr the array to fill, must be initialized with init_btree_arr()
 */
void	btree_to_arr(t_btnode *root, int depth, int id, void ***btree_arr)
{
	if (root == NULL)
		return ;
	btree_to_arr(root->left, depth + 1, id + id + depth, btree_arr);
	btree_arr[depth][id - get_id_offset(depth)] = root;
	btree_to_arr(root->right, depth + 1, id + id + depth + 1, btree_arr);
}
