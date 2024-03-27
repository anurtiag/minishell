/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:06:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 21:14:56 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	*reset_statics(int mode, int *array, t_var_parsed_table **table_node)
{
	if (mode == 2)
	{	
		array[FIRST] = 1;
		free_parsed_table(table_node);
		return (array);
	}
	if (mode == 1)
	{
		array[RTF] = 0;
		array[RFF] = 0;
		array[EF] = 0;
		array[FD]= -1;
		return (array);
	}
}

void	init_append_tree(t_token *tree, int *first_time, t_var_parsed_table **table_node)
{
	if (tree->type == 100 || tree->type == 101)
	{
		if (*first_time == 1)
		{
			*table_node = init_parsed_table(*table_node);
			*first_time = 0;
		}
		else
		{
			(*table_node)->next = init_parsed_table(*table_node);
			*table_node = (*table_node)->next;
		}
	}
}

void	set_fds(int *array, t_var_parsed_table **table_node)
{
	if (array[RFF] == 1 || array[HDF] == 1)
		(*table_node)->fd_in = array[FD];
	if (array[RTF] == 1 || array[APPF] == 1)
	{
		if (array[EF] == 1)
			(*table_node)->fd_error = array[FD];
		else
			(*table_node)->fd_out = array[FD];
	}
}

void	create_table(t_token *tree, t_var_parsed_table **table_node)
{
	if (((tree->type == 0 || tree->type == 102 || tree->type == 103 || \
	tree->type == 105 || tree->type == 100 || tree->type == 101) && \
	(tree->left == NULL && tree->middle == NULL && tree->right == NULL)))
	{
		if ((*table_node)->cmd == NULL)
			(*table_node)->cmd = strdup(tree->data);
		else
		{
			(*table_node)->cmd = realloc((*table_node)->cmd, ft_strlen((*table_node)->cmd) + ft_strlen(tree->data) + 2);
			ft_strlcat((*table_node)->cmd, " ", (ft_strlen((*table_node)->cmd) + ft_strlen(" ") + 1));
			ft_strlcat((*table_node)->cmd, tree->data, (ft_strlen((*table_node)->cmd) + ft_strlen(tree->data) + 1));
		}
	}
}

int	*set_flags(t_token *tree, int *array)
{
	if (tree->type == 2)
		array[RFF] = 1;
	if (tree->type == 3)
		array[HDF] = 1;
	if (tree->type == 4)
		array[APPF] = 1;
	if (tree->type == 1)
	{
		array[RTF] = 1;
		if (ft_strcmp(tree->data, "2>") == 0)
			array[EF] = 1;
	}
	return (array);
}
