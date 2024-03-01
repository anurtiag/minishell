/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:46:59 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/01 13:52:36 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void read_tree(t_token *tree, char ***data_ptr, int *count) {
	if (tree == NULL)
		return;

	// Process left child
	if (tree->left)
		read_tree(tree->left, data_ptr, count);
		
	// Process middle child
	if (tree->middle)
		read_tree(tree->middle, data_ptr, count);
		
	// Process right child
	if (tree->right)
		read_tree(tree->right, data_ptr, count);

	// Process current node
	if ((tree->type == 0 || tree->type == 102 || tree->type == 103 || tree->type == 105) && (tree->left == NULL && tree->middle == NULL && tree->right == NULL))
	{
		printf("%s %i\n", tree->data, *count);
		*count += 1;
	}
}

void	walk_tree(t_input **input_struct, t_token *tree)
{
	int count;
	char **line;
	int	i;

	i = 0;
	line = NULL;
	count = 0;
	
	if (tree->left && tree->left->type == 100)
		walk_tree(input_struct, tree->left);

	if (tree->left->type == 100)
		read_tree(tree->right, &line, &count);
	else
		read_tree(tree, &line, &count);

}