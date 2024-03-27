/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_read_tree_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:06:52 by emimenza          #+#    #+#             */
/*   Updated: 2024/03/27 13:42:04 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	reset_statics(int mode, int *first_time, int *red_to_flag, int *red_from_flag, int *error_flag, int *fd, t_var_parsed_table **table_node)
{
	if (mode == 2)
	{
		*first_time = 1;
		free_parsed_table(table_node);
		return ;
	}
	if (mode == 1)
	{
		*red_to_flag = 0;
		*red_from_flag = 0;
		*error_flag = 0;
		*fd = -1;
		return ;
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

void	set_fds(int red_from_flag, int red_to_flag, int here_doc, int append, int error_flag, t_var_parsed_table **table_node, int fd)
{
	if (red_from_flag == 1 || here_doc == 1)
		(*table_node)->fd_in = fd;
	if (red_to_flag == 1 || append == 1)
	{
		if (error_flag == 1)
			(*table_node)->fd_error = fd;
		else
			(*table_node)->fd_out = fd;
	}
}

void	create_table(t_token *tree, t_var_parsed_table **table_node)
{
	if (((tree->type == 0 || tree->type == 102 || tree->type == 103 || tree->type == 105 || tree->type == 100 || tree->type == 101) && (tree->left == NULL && tree->middle == NULL && tree->right == NULL)))
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

void	set_flags(t_token *tree, int *red_from_flag, int *here_doc, int *append, int *red_to_flag, int *error_flag)
{
	if (tree->type == 2)
		*red_from_flag = 1;
	if (tree->type == 3)
		*here_doc = 1;
	if (tree->type == 4)
		*append = 1;
	if (tree->type == 1)
	{
		*red_to_flag = 1;
		if (ft_strcmp(tree->data, "2>") == 0)
			*error_flag = 1;
	}
}
