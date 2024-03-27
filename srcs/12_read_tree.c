/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:46:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 21:13:06 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

//Frees the parsed table node
void	free_parsed_table(t_var_parsed_table **table)
{
	t_var_parsed_table	*temp;

	while ((*table) != NULL)
	{
		temp = (*table)->next;
		free_double((*table)->cmd_splited);
		free((*table)->cmd);
		free((*table)->path);
		free(*table);
		(*table) = temp;
	}
}

//Inits and creates node for parsed table
t_var_parsed_table	*init_parsed_table(t_var_parsed_table *prev_table)
{
	t_var_parsed_table	*node;

	node = (t_var_parsed_table *)malloc(sizeof(t_var_parsed_table));
	if (node)
	{
		node->cmd = NULL;
		node->cmd_splited = NULL;
		node->env = NULL;
		node->fd_error = -1;
		node->fd_in = -1;
		node->fd_out = -1;
		node->next = NULL;
		node->path = NULL;
		node->pid = 0;
		node->prev = prev_table;
	}
	return (node);
}

//Recursive function to read the data of the tree
void	read_tree(t_token *tree, t_var_parsed_table **table_node, int mode)
{
	static int array[7] = {1, 0, 0 , 0, 0, 0, -1};

	if (tree == NULL)
		return ;
	reset_statics(mode, array, table_node);
	init_append_tree(tree, &array[FIRST], table_node);
	set_flags(tree, array);
	if (tree && tree->right && (tree->right->type == 108 || tree->right->type == 110))
	{
		if (tree->left && tree->left->type == 1)
			array[FD] = open(tree->right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tree->left && tree->left->type == 2)
			array[FD] = open(tree->right->data, O_RDONLY);
		else if (tree->left && tree->left->type == 3)
			array[FD] = ft_here_doc(tree->right->data, 0);
		else if (tree->left && tree->left->type == 4)
			array[FD] = open(tree->right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (tree->left != NULL)
		read_tree(tree->left, table_node, 0);
	if (tree->middle != NULL)
		read_tree(tree->middle, table_node, 0);
	if (tree->right != NULL)
		read_tree(tree->right, table_node, 0);
	create_table(tree, table_node);
	set_fds(array, table_node);
}

//Looks for sub_trees in the main tree
void	walk_tree(t_var_parsed_table **parsed_table, t_token *tree)
{
	int	control;

	control = TRUE;
	if (tree->left && tree->left->type == 100)
		walk_tree(parsed_table, tree->left);
	if (tree->left && tree->left->type == 100)
		read_tree(tree->right, parsed_table, 0);
	else
		read_tree(tree, parsed_table, 0);
	read_tree(tree, parsed_table, 1);
}
