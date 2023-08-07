/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenlst_management.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/12 20:27:17 by ewehl         #+#    #+#                 */
/*   Updated: 2023/08/04 19:35:06 by ewehl         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

/**
 * @brief Initialize a token list with an empty head and length of zero.
 *
 * @param tlist The token list to initialize.
 */
void	init_tlst(t_token_lst *tlist)
{
	tlist->len = 0;
	tlist->head = NULL;
}

/**
 * @brief Adds a node to the end of the token list.
 *
 * @param tlist A pointer to the token list where the node will be added.
 * @param node The node to be added.
 */
void	add_node(t_token_lst **tlist, t_token *node)
{
	t_token	*c_node;

	c_node = (*tlist)->head;
	if (!c_node)
		(*tlist)->head = node;
	else
	{
		while (c_node && c_node->next != NULL)
			c_node = c_node->next;
		c_node->next = node;
	}
	(*tlist)->len++;
}

/**
 * @brief Create a token list from a given string.
 *
 * @param tlist The token list to be populated.
 * @param str The string from which tokens will be created.
 * @param strlen The length of the string.
 */
void	make_token_list(t_token_lst	*tlist, char *str, int strlen)
{
	int			start;
	t_token		*node;

	start = 0;
	init_tlst(tlist);
	while (start < strlen)
	{
		node = get_next_token(str, &start);
		if (!node && !tlist->head)
			return ;
		else if ((!node && start == strlen))
			return ;
		else if (!node && tlist->head)
		{
			free_token_struct(tlist);
			return ;
		}
		add_node(&tlist, node);
	}
}

/**
 * @brief Print the token list.
 *
 * @param tlist The token list to be printed.
 */
void	print_token_lst(t_token_lst tlist)
{
	t_token	*tmp;
	int		idx;

	idx = 0;
	tmp = tlist.head;
	while (tmp && idx < tlist.len)
	{
		ft_printf("[%d] value : %s :: type : %d\n", idx, tmp->value, tmp->type);
		tmp = tmp->next;
		idx++;
	}
}

/**
 * @brief Frees the token structure.
 *
 * Also sets the values of token->head and token to NULL
 * 
 * @param token The token structure to be freed.
 */
void	free_token_struct(t_token_lst *token)
{
	t_token	*tmp;

	if (token->head)
	{
		tmp = (token)->head;
		while (tmp)
		{
			token->head = token->head->next;
			free(tmp->value);
			free(tmp);
			tmp = token->head;
		}
	}
	token->head = NULL;
	token = NULL;
}
